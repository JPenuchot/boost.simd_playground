#!/usr/bin/env node

const fs = require('fs');

//	Checking for args being filled
//if(process.argv.length != 4){
//	console.log("link-parser : Parses links that got tagged with a given string in your Facebook Group's posts.");
//	console.log("Usage : link-parser [DATA_PATH] [TAG]");
//	return;
//}

/**
 * Converts a JSON benchmark element from Google Benchmark to something more usable.
 *
 * @param      {gbenchmark_json_element}  elmt    Element from Google Benchmark
 */
function parse_elmt(elmt){
	//	Parsing
	let elmts = elmt.name.split("__");
	let tail = elmts[3].split("_");

	let ret = {
		task : elmts[0],
		structure : elmts[1],
		method : elmts[2],
		size : parseInt(tail[0]),
		kind : tail[1],
		time : elmt.cpu_time,
		unit : elmt.time_unit,
	}

	console.log(ret);
}

//	Retreiving args
const default_data_path = "../output/report.json";
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_out_path = "../output/report.csv";
const out_path = process.argv[3] ? process.argv[3] : default_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);

console.log(parsedJson.benchmarks[2]);

parse_elmt(parsedJson.benchmarks[2]);