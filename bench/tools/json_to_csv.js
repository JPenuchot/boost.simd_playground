#!/usr/bin/env node

const fs = require('fs');

//	Checking for args being filled
//if(process.argv.length != 4){
//	console.log("link-parser : Parses links that got tagged with a given string in your Facebook Group's posts.");
//	console.log("Usage : link-parser [DATA_PATH] [TAG]");
//	return;
//}

function parse_name(elmt){
	elmt.name.split(" ");
}

//	Retreiving args
const default_data_path = "../output/report.json"
const data_path = process.argv[2] ? process.argv[2] : default_data_path;

const default_out_path = "../output/report.csv";
const out_path = process.argv[3] ? process.argv[3] : default_out_path;

//	Reading files
const rawJson = fs.readFileSync(data_path);
const parsedJson = JSON.parse(rawJson);

console.log(parsedJson.benchmarks[0]);