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
		size : parseInt(tail[0]),
		time : elmt.cpu_time,
		unit : elmt.time_unit,
	};
}

//	Retreiving args
const default_data_path = "../output/report.json";
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_out_path = "../output/report.csv";
const out_path = process.argv[3] ? process.argv[3] : default_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);

//	Header
let out_buffer = "task,structure,method,size,time,unit\n";

//	Writing CSV format
parsedJson.benchmarks.forEach(elmt => {
	let ne = parse_elmt(elmt);
	if(ne)
		out_buffer += 
			ne.task + ','
		+	ne.structure + ','
		+	ne.method + ','
		+	ne.size + ','
		+	ne.time + ','
		+	ne.unit
		+	'\n';
});

//	Writing file
fs.writeFile(out_path, out_buffer, err => {
  if (err) throw err;
  console.log('Converted ' + data_path + ' to ' + out_path);
});