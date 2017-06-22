#!/usr/bin/env node

const fs = require('fs');
const plot = require('plotter').plot;

/**
 * Converts a JSON benchmark element from Google Benchmark to something more usable.
 *
 * @param      {gbenchmark_json_element}  elmt    Element from Google Benchmark
 */
function parse_elmt(elmt){
	//	Parsing
	let elmts = elmt.name.split("__");
	let tail = elmts[3].split("_");

	if(tail[1] == "stddev") return;
	else return {
		task : elmts[0],
		structure : elmts[1],
		method : elmts[1] + "_" + elmts[2],
		size : tail[0],
		time : elmt.cpu_time,
		unit : elmt.time_unit,
	};
}

/**
 * Lists all the methods used in a bench
 *
 * @param      {gbenchmark_json}  pJSON   Google Benchmark parsed JSON
 */
function list_methods(pJSON){
	let ret = new Array();
	pJSON.forEach(elmt => {
		if(!ret.find(e => e == elmt.method)) ret.push(elmt.method);
	});
	return ret.sort();
}

/**
 * Lists all the sizes used in a bench
 *
 * @param      {gbenchmark_json}  pJSON   Google Benchmark parsed JSON
 */
function list_sizes(pJSON){
	let ret = new Array();
	pJSON.forEach(elmt => {
		if(!ret.find(e => e == elmt.size)) ret.push(elmt.size);
	});
	return ret.sort((a,b) => a - b);
}

/*
 *	CODE
 */

//	Checking for args being filled
if(process.argv.length != 5){
	console.log("json_to_csv.js : Parses JSON formatted benchmark results into plottable CSV results.");
	console.log("Usage : json_to_csv.js [INPUT_JSON] [OUTPUT_CSV] [OUTPUT_SVG]");
	return;
}

//	Retreiving args
const default_data_path = "../output/report.json";
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_csv_out_path = "../output/report.csv";
const csv_out_path = process.argv[3] ? process.argv[3] : default_csv_out_path;

const default_svg_out_path = "../output/graph.svg";
const svg_out_path = process.argv[4] ? process.argv[4] : default_svg_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);
const benches = parsedJson.benchmarks.map(parse_elmt);

let sz_list = list_sizes(benches);
let mt_list = list_methods(benches);

let bench_map = {};
let mplot = {};

//	Building bench_map (Associates (size, method) to the timing)

benches.forEach(elmt => {
	if(!bench_map[elmt.size])
		bench_map[elmt.size] = {};
	bench_map[elmt.size][elmt.method] = elmt.time;
});

/*
 *	CSV Writing
 */

// Header
let sres = "#size,";
mt_list.forEach(val => sres += val + ',');

//	Body
sz_list.forEach(sz => {
	sres += '\n' + sz + ',';
	mt_list.forEach(mt => sres += bench_map[sz][mt] + ',');
});

//	Writing file
fs.writeFile(csv_out_path, sres, err => { if (err) throw err; });

/*
 * Plotting
 */

//	Building plot map

mt_list.forEach(mt =>{
	mplot[mt] = {};
	sz_list.forEach(sz => {
		mplot[mt][sz] = bench_map[sz][mt];
	});
});

//	Actual plotting

plot({
	data:		mplot,
	filename:	svg_out_path,
	style:		'linespoints',
	//title:		'Example \'Title\', \\n runs onto multiple lines',
	logscale:	true,
	xlabel:		'Element count',
	ylabel:		'Time',
	format:		'svg'
});