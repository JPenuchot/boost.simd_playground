#!/usr/bin/env node

const fs = require('fs');

//	Checking for args being filled
if(process.argv.length != 4){
	console.log("json_to_csv.js : Parses JSON formatted benchmark results into plottable CSV results.");
	console.log("Usage : json_to_csv.js [INPUT_JSON] [OUTPUT_CSV]");
	return;
}

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
		method : elmts[2],
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
	pJSON.benchmarks.forEach(input => {
		let elmt = parse_elmt(input)
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
	pJSON.benchmarks.forEach(input => {
		let elmt = parse_elmt(input)
		if(!ret.find(e => e == elmt.size)) ret.push(elmt.size);
	});
	return ret.sort((a,b) => a - b);
}

//	Retreiving args
const default_data_path = "../output/report.json";
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_out_path = "../output/report.csv";
const out_path = process.argv[3] ? process.argv[3] : default_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);

let sz_list = list_sizes(parsedJson);
let mt_list = list_methods(parsedJson);

let bench_mat = {};

parsedJson.benchmarks.forEach(input =>{
	let elmt = parse_elmt(input);
	if(elmt){
		if(bench_mat[elmt.size])
			bench_mat[elmt.size][elmt.method] = elmt.time;
		else{
			bench_mat[elmt.size] = {};
			bench_mat[elmt.size][elmt.method] = elmt.time;
		}
	}
});

console.log(sz_list);
//console.log(mt_list);
//console.log(bench_mat);

let sres = "size,";

//	Header
mt_list.forEach(mt => {
	sres += mt + ","
});

sres += '\n';

//	Body
sz_list.forEach(sz => {
	sres += sz + ','
	mt_list.forEach(mt => sres += bench_mat[sz][mt] + ',');
	sres += '\n';
});

//	Writing file
fs.writeFile(out_path, sres, err => {
  if (err) throw err;
  console.log('Converted ' + data_path + ' to ' + out_path);
});