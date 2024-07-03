#include "OBJ.h"
#include <string>
#include <set>
#include <cctype>

using namespace std;

// ###########################################################
// OBJFace
// ###########################################################

string OBJFace::to_line()const{
	string result = "f ";

	for (uint8_t i = 0; i < 3; i++) {
		result += to_string(vertices[i]);

		if (textures[i]!=0 || normals[i]!=0) {
			result += '/';

			if (textures[i]!=0)
				result += to_string(textures[i]);
			
			if (normals[i]!=0){
				result += '/';
				result += to_string(normals[i]);
			}
		}
		
		if (i != 2)
			result += ' ';
	}
	
	return result;
};

// ###########################################################
// COMPRESSOR
// ###########################################################

OBJ::OBJCompressionNode::OBJCompressionNode(
	OBJ *referral,
	OBJFace *face, 
	OBJ::OBJCompressionNode *next): 
	referral(referral),
	face(face), 
	next(next) {}

OBJ::OBJCompressionNode::OBJCompressionNode(
	OBJ *referral,
	OBJFace *face): 
	OBJ::OBJCompressionNode::OBJCompressionNode(
		referral, 
		face, 
		nullptr
	) {}

OBJ::OBJCompressionNode::~OBJCompressionNode(){
	for (uint8_t i = 0; i < 3; i++) {
		// vertex set
		int found_j = referral
			->vertices
			->find(
				vertices[i]
			);

		face->set_vertex(i, found_j + 1);
		vertices[i] = nullptr;

		// normal set
		if (face->get_normal_p(i)!=0)
			face->set_normal(
				i, 
				referral->normals->find(normals[i]) + 1
			);

		normals[i] = nullptr;
		
		// texture set
		if (face->get_texture_p(i)!=0)
			face->set_texture(
				i, 
				referral->textures->find(textures[i]) + 1
			);
		
		textures[i] = nullptr;
	}

	referral = nullptr;
	face = nullptr;
	
	delete next;
};

OBJ::OBJCompressionNode* OBJ::OBJCompressionNode::get_next(
	const uint32_t &ahead) {
	OBJCompressionNode* current = this;

	for (size_t i = 0; i < ahead; i++)
		current = current->next;
	
	return next;
};
// ###########################################################
// MAIN OBJ 
// ###########################################################

// SPECIFIC_ENUM
enum OBJ_LINE_TYPE {
	LINE_TYPE_UNKNOWN,
	LINE_TYPE_NAME,
	LINE_TYPE_VERTEX,
	LINE_TYPE_NORMAL,
	LINE_TYPE_TEXTURE,
	LINE_TYPE_FACE,
	LINE_TYPE_COMMENT,
	LINE_TYPE_NOTHING
};

// FUNCTIONS
/**
 * Takes in reference as a string, returns an int as an enum
*/
OBJ_LINE_TYPE name_to_line_type(const string &reference){
	if (reference == "o") return LINE_TYPE_NAME;
	if (reference == "v") return LINE_TYPE_VERTEX;
	if (reference == "vn") return LINE_TYPE_NORMAL;
	if (reference == "vt") return LINE_TYPE_TEXTURE;
	if (reference == "f") return LINE_TYPE_FACE;
	if (reference == "#") return LINE_TYPE_COMMENT;
	if (reference.size() == 0) return LINE_TYPE_NOTHING;

	return LINE_TYPE_UNKNOWN;
}

bool check_istream(istream &input){
	return input.bad() || input.fail();
}

Vector3* istream_to_Vector3(istream &input){
	float x, y, z;
	input >> x >> y >> z;

	if (input.bad() || input.fail()) {
		cerr << "Failed conversion Vector3: resulted"
			<< " in input bad or fail\n";
		return nullptr;
	}
	
	return new Vector3(x,y,z);
}

Vector2* istream_to_Vector2(istream &input){
	float x, y;
	input >> x >> y;

	if (input.bad() || input.fail()) {
		cerr << "Failed conversion Vector2: resulted in input bad or fail\n";
		return nullptr;
	}
	
	return new Vector2(x,y);
}

LinkedList<string>* split(const string &main, const string &delim){
	auto list = new LinkedList<string>();

	if (delim.length() == 0) {
		const unsigned int n = main.length();

		for (unsigned int i = 0; i < n; i++){
			string c = main.substr(i, 1);
			list->insert(&c);
		}
	} else {
		size_t i = main.find(delim),
			j = 0;

		while (i != string::npos) {
			list->insert(
				new string(main.substr(j,i-j))
			);
			j = i + delim.length();
			i = main.find(delim, j);
		}

		auto last = new string(main.substr(j, string::npos));

		list->insert(last);
	}
	
	return list;
}

template <typename T>
inline string to_string(const set<T> &value){
	string result = "Set{";

	set<uint32_t>::const_iterator i = value.begin(), 
		end = value.end();

	if (i == end) return result + '}';
	
	result += to_string(*i);

	for (i++; i != end; i++)
		result += ", " + to_string(*i);

	return result + '}';
}

vector<string>* split_to_vector(
	const string &main, 
	const string &delim){
	LinkedList<string> *list = split(main, delim);
	vector<string>* result = list->to_vector();
	list->detatch_all();
	delete list;
	return result;
}

// CONSTRUCTORS
OBJ::OBJ() {
	__init();
	vertices = new VectorNVector<Vector3>();
	normals = new VectorNVector<Vector3>();
	textures = new VectorNVector<Vector2>();
}

/**
 * Automatically parses input stream
*/
OBJ::OBJ(istream &input) {
	__init();
	this->is_constructed = false;

	auto vertices = new LinkedList<Vector3>();
	auto normals = new LinkedList<Vector3>();
	auto textures = new LinkedList<Vector2>();

	while (!input.eof()) 
		if (!parse_line(input, vertices, normals, textures)) 
			return;
	
	vector<Vector3*>* temp = (vertices->to_vector_of_pointers());
	
	this->vertices = new VectorNVector(*temp, true);
	delete temp;

	temp = normals->to_vector_of_pointers();
	this->normals = new VectorNVector(*temp, true);
	delete temp;

	vector<Vector2*> *temp2 = textures->to_vector_of_pointers();
	this->textures = new VectorNVector(*temp2, true);
	delete temp2;

	vertices->detatch_all();
	normals->detatch_all();
	textures->detatch_all();

	delete vertices, normals, textures;

	this->is_constructed = true;
}

// METHODS
string* OBJ::peek_prefix(istream &input)const{
	string *result = new string();
	bool in_loop = true;

	while(in_loop && !input.eof()){
		char c = input.get();
		 
		if (c == '#') {
			*result += c;
			in_loop = false;
		} else if (c == '\n' || c==-1)
			continue;
		else if (isspace(c))
			in_loop = false;
		else
			*result += c;
	}

	return result;
};

/**
 * parses a line unit from input, returns success
 * 
*/
bool OBJ::parse_line(
	istream &input,
	LinkedList<Vector3> *vertices,
	LinkedList<Vector3> *normals,
	LinkedList<Vector2> *textures){
	
	string *line_type_name = peek_prefix(input);

	if ((input.bad() || input.fail()) && !input.eof()) {
		cerr << "Main construction: Input bad or failed\n";
		return false;
	}

	auto line_type = name_to_line_type(*line_type_name);

	switch (line_type) {
		case LINE_TYPE_VERTEX:{
			Vector3* vertex = istream_to_Vector3(input);
			if (vertex == nullptr) return false;
			vertices->insert(vertex);
			break;
		}case LINE_TYPE_NORMAL:{
			Vector3* normal = istream_to_Vector3(input);
			if (normal == nullptr) return false;
			normals->insert(normal);
			break;
		}case LINE_TYPE_TEXTURE: {
			Vector2* texture = istream_to_Vector2(input);
			if (texture == nullptr) return false;
			textures->insert(texture);
			break;
		}case LINE_TYPE_FACE:{
			if (!parse_face(input)) return false;
			break;
		}case LINE_TYPE_NAME:
		 case LINE_TYPE_COMMENT: {
			getline(input, *line_type_name);
		}case LINE_TYPE_NOTHING:
			break;
		default:
			throw runtime_error("Construction: File parsing: caught unknown line type: " + *line_type_name);
			break;
	}

	delete line_type_name;

	return true;
}

bool OBJ::parse_face(istream &input){
	uint32_t f_vertices[3] = {0, 0, 0};
	uint32_t f_normals[3] = {0, 0, 0};
	uint32_t f_textures[3] = {0, 0, 0};
	
	vector<string> *sections = nullptr;

	for (uint8_t i = 0; i < 3; i++) {
		string point_section;
		delete sections;
		input >> point_section;
		sections = 
			split_to_vector(point_section, "/");
		
		f_vertices[i] = stoi(sections->at(0));

		if (sections->size() <= 1) continue;
		
		if (sections->at(1).length() != 0)
			f_textures[i] = stoi(sections->at(1));
		
		if (sections->size() == 2) continue;
		
		f_normals[i] = stoi(sections->at(2));
	}

	faces->insert(
		new OBJFace(this, f_vertices, f_normals, f_textures)
	);

	return true;
}

void OBJ::compress(){
	OBJCompressionNode *head = nullptr,
		*current_node = nullptr;

	auto short_access_vertices = new set<uint32_t>(),
		short_access_normals = new set<uint32_t>(),
		short_access_textures = new set<uint32_t>();

	
	// mark all dupes in lists
	for (auto current=faces->get_head();
		current!=nullptr;
		current=current->get_next()) {
		
		OBJFace *face = current->get_value();
		
		// eval current node
		if (head == nullptr) 
			current_node = 
				head = new OBJCompressionNode(this, face);
		else{
			current_node->next = new OBJCompressionNode(
				this, 
				face
			);
			current_node = current_node->next;
		}
		
		// set values
		for (uint8_t i = 0; i < 3; i++) {
			// eval vertex
			int found_p = vertices->find(face->get_vertex(i));
			current_node->vertices[i] = vertices->at(found_p);
			short_access_vertices->insert(found_p);

			// eval normals
			if (face->get_normal_p(i)!=0) {
				found_p = normals->find(face->get_normal(i));
				current_node->normals[i] = normals->at(found_p);
				short_access_normals->insert(found_p);
			}

			// eval textures
			if (face->get_texture_p(i)==0) continue;
			
			found_p = textures->find(face->get_texture(i));
			current_node->textures[i] = textures->at(found_p);
			short_access_textures->insert(found_p);
		}
	}


	// use sets to keep lists
	vertices->intersection_i(*short_access_vertices);
	delete short_access_vertices;
	
	normals->intersection_i(*short_access_normals);
	delete short_access_normals;
	
	textures->intersection_i(*short_access_textures);
	delete short_access_textures;

	// compress
	vertices->remove_nulls();
	normals->remove_nulls();
	textures->remove_nulls();
	

	// return
	delete head;

}

void OBJ::write_out(ostream &out) const {
	for (uint32_t i = 0,
		n = vertices->size(); 
		i < n; i++) {

		Vector3 *vertex = vertices->at(i);
		
		out << "v " 
			<< vertex->x() 
			<< ' ' 
			<< vertex->y()
			<< ' '
			<< vertex->z()
			<< endl;
	}
	
	for (uint32_t i = 0, 
		n = normals->size(); 
		i < n; i++) {
		Vector3* normal = normals->at(i);
		
		out << "vn " 
			<< normal->x() 
			<< ' ' 
			<< normal->y()
			<< ' '
			<< normal->z()
			<< endl;
	}

	for (uint32_t i = 0, 
		n = textures->size(); 
		i < n; i++) {
		Vector2* texture = textures->at(i);
		
		out << "vt " 
			<< texture->x() 
			<< ' ' 
			<< texture->y()
			<< endl;
	}

	for (auto current = faces->get_head();
		current != nullptr; 
		current = current->get_next()) {
		auto face = current->get_value();
		
		out << face->to_line() << endl;
	}
}


