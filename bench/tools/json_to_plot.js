#!/usr/bin/env node

const fs = require('fs');

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
		category : elmts[0],
		structure : elmts[1],
		name : (elmts[1] + " : " + elmts[2]).replace("_", " "),
		size : tail[0],
		time : elmt.cpu_time,
		unit : elmt.time_unit,
	};
}

function list_methods(pJSON){
	let ret = new Array();
	pJSON.forEach(elmt => {
		if(!ret.find(e => e == elmt.method)) ret.push(elmt.method);
	});
	return ret.sort();
}

function list_sizes(pJSON){
	let ret = new Array();
	pJSON.forEach(elmt => {
		if(!ret.find(e => e == elmt.size)) ret.push(elmt.size);
	});
	return ret.sort((a,b) => a - b);
}

function list_categories(pJSON){
	let ret = [];
	pJSON.forEach(elmt => {
		if(!ret.find(e => e == elmt.category)) ret.push(elmt.category);
	});
	return ret.sort();
}

function separate_categories(pJSON){
	let ret = {};
	list_categories(pJSON).forEach(cat => ret[cat] = pJSON.filter(elmt => elmt.category == cat));
	return ret;
}

/*
 *	CODE
 */

//	Checking for args being filled
if(process.argv.length != 4){
	console.log("json_to_svg.js : Renders JSON formatted benchmark results into SVG plots.");
	console.log("Usage : bench_plotter.js [INPUT_JSON] [OUTPUT]_<category>.svg");
	return;
}

//	Retreiving args
const default_data_path = "../output/report.json";
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_csv_out_path = "../output/report.csv";
const csv_out_path = process.argv[3] ? process.argv[3] : default_csv_out_path;

const default_svg_out_path = "../output/graph.svg";
const svg_out_path = process.argv[3] ? process.argv[3] : default_svg_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);
const benches = parsedJson.benchmarks.map(parse_elmt);

const benches_sep = separate_categories(benches);
const categories = list_categories(benches);

console.log(categories);

categories.forEach(cat => {
	let mplot = {};

	benches_sep[cat].forEach(bench => {
		if(!mplot[bench.name])
			mplot[bench.name] = {};
		
		mplot[bench.name][bench.size] = bench.time;
	});

	let plot = require('plotter').plot;

	plot({
			data:		mplot,
			filename:	svg_out_path + '_' + cat + '.svg',
			style:		'linespoints',
			//title:		'Example \'Title\', \\n runs onto multiple lines',
			logscale:	true,
			xlabel:		'Bench size',
			ylabel:		'Time (lower is better)',
			format:		'svg'
		});
});
