#include <iostream>
#include <string>
#include <fstream>
#include "StopWatch.h"
#include "MESH.h"

using namespace std;

enum MENU_OPTION {EXIT, CONVERT_TO_MESH, COMPRESS_OBJ};

MENU_OPTION max_option = COMPRESS_OBJ;

void print_menu() {
	cout << "Enter number:\n"
		<< EXIT << ": Exit\n"
		<< CONVERT_TO_MESH << ": Convert to mesh\n"
		<< COMPRESS_OBJ << ": Transform input obj mesh to "
			<< "smaller obj mesh\n";
}

MENU_OPTION get_option(){
	int result;

	while (true){
		cin >> result;
		
		if (result < 0 && result > max_option) {
			cout << "Enter a valid option.\n";
			continue;
		}

		break;
	}
	
	return static_cast<MENU_OPTION>(result);
}

string* get_file_name_no_ext(const string &ref){
	int found = ref.find_last_of('.');

	if (found == string::npos)
		return new string(ref);
	
	return new string(ref.substr(0, found));
}

void convert_to_mesh(){
	cout << "Method begin: convert_to_mesh\n";

	// get input
	cout << "Drag file here, type file path or "
		<< "type 'd' for default: ";

	string input_path; cin >> input_path;

	if (input_path.length() == 1 && input_path.at(0) == 'd')
		input_path = "../dev_in.txt";

	ifstream *input_file = new ifstream(input_path);
	
	if (!input_file->is_open()) {
		cout << "Terminated: "
			<< input_path
			<<" inaccessable.";
		delete input_file;
		return;
	}

	auto no_ext = get_file_name_no_ext(
		input_path);

	// get output
	ofstream *output_file = new ofstream(
		*no_ext + "_out.mesh", 
		ios::binary
	);

	delete no_ext;

	if (!output_file->is_open()) {
		cout << "Terminated: out.mesh inaccessable";
		input_file->close();
		output_file->close();
		delete input_file, output_file;
		return;
	}
	
	cout << "Building OBJ: ";
	auto watch = new StopWatch(); watch->start();
	OBJ *obj = new OBJ(*input_file);

	cout << watch->hop() << "s\n"
		<< "Compressing: ";
	obj->compress();

	cout << watch->hop() << "s\n"
		<< "Building MESH: ";
	MESH *mesh = new MESH(obj);

	cout << watch->hop() << "s\n"
		<< "Writing to output file: ";
	mesh->write_out(*output_file);
	cout << watch->hop() << "s\n";

	output_file->close();
	input_file->close();

	delete input_file, mesh, output_file, obj;
}

void compress_obj(){
	cout << "Method begin: compress_obj\n";
	// get input
	ifstream *input_file = new ifstream("../dev_in.txt");
	
	if (!input_file->is_open()) {
		cout << "Terminated: in.txt inaccessable.\n";
		input_file->close();
		delete input_file;
		return;
	}
	
	// get output
	ofstream *output_file = new ofstream("../dev_out.obj");
	if (!output_file->is_open()) {
		cout << "Terminated: out.obj is inaccessable.\n";
		input_file->close();
		output_file->close();
		delete input_file, output_file;
	}

	cout << "Building OBJ: ";
	auto watch = new StopWatch(); watch->start();
	OBJ *obj = new OBJ(*input_file);
	
	cout << watch->hop() << "s\n"
		<< "Compressing: ";
	obj->compress();

	cout << watch->hop() << "s\n"
		<< "Writing result: ";
	obj->write_out(*output_file);

	cout << watch->hop() << "s\n";
	output_file->close();
	input_file->close();
	cout << "done.\n";
	delete obj, output_file, input_file, watch;
}

int main(int argc, char const *argv[]) {
	MENU_OPTION response;

	while (true) {
		print_menu();

		response = get_option();

		switch (response) {
			case EXIT:break;
			case CONVERT_TO_MESH:
				convert_to_mesh();
				break;
			case COMPRESS_OBJ:
				compress_obj();
				break;
			default:
				cout << "Unimplemented number: got " 
					<< response 
					<< endl;
				break;
		}

		if (response == EXIT) break;
	}
	return 0;
}

