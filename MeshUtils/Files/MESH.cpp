#include "MESH.h"
#include "BOSWrapper.h"
#include "Color3a.h"

using namespace std;

// #############################################
// TANGENT
// #############################################

// CONSTRUCTORS
MESHTangent::MESHTangent(
	const int8_t &x0,
	const int8_t &y0,
	const int8_t &z0,
	const int8_t &s0){
	x(x0);
	y(y0);
	z(z0);
	s(s0);
}

// METHODS
int8_t MESHTangent::x()const{return _x;};
void MESHTangent::x(const int8_t &alt){_x=alt;};
int8_t MESHTangent::y()const{return _y;};
void MESHTangent::y(const int8_t &alt){_y=alt;};
int8_t MESHTangent::z()const{return _z;};
void MESHTangent::z(const int8_t &alt){_z=alt;};
int8_t MESHTangent::s()const{return _s;};
void MESHTangent::s(const int8_t &alt){_s=alt;};

// STATICS
MESHTangent MESHTangent::default_obj = 
	MESHTangent();

MESHTangent* MESHTangent::get_default(){
	return &MESHTangent::default_obj;
}

// #############################################
// MESH
// #############################################

// STATICS
string MESH::file_version = "version 2.00";

// CONSTRUCTORS
MESH::MESH(OBJ *obj){
	vertices = new VectorNVector<Vector3>(obj->get_vertices_size());
	normals = new VectorNVector<Vector3>(obj->get_normals_size());
	textures = new VectorNVector<Vector2>(obj->get_textures_size());

	// Typical defaults
	header_size = 0x0C;
	vertex_size = 0x28;
	face_size = 0x0C;

	// Population
	uint32_t n = vertices->size(),
		i = 0;

	for (; i < n; i++)
		vertices->at(i) = new Vector3(*obj->get_vertex(i));
	for (i = 0, n = normals->size(); i < n; i++)
		normals->at(i) = new Vector3(*obj->get_normal(i));
	for (i = 0, n = textures->size(); i < n; i++)
		textures->at(i) = new Vector2(*obj->get_texture(i));
	
	faces = new LinkedList<MESHFace>();

	for (auto current = obj->get_face_head();
		current != nullptr;
		current = current->get_next()) {
		auto value = current->get_value();
		uint32_t vertices_p[3] = {0,0,0};
		uint32_t normals_p[3] = {0,0,0};
		uint32_t textures_p[3] = {0,0,0};

		for (uint8_t i = 0; i < 3; i++) {
			vertices_p[i] = value->get_vertex_p(i);
			normals_p[i] = value->get_normal_p(i);
			textures_p[i] = value->get_texture_p(i);
		}
		
		faces->insert(
			new MESHFace(this, vertices_p, normals_p, textures_p)
		);
	}
}

// METHODS
void MESH::write_out(std::ostream &out) const {
	uint32_t face_amount = faces->size();
	uint32_t vertex_amount = face_amount * 3;

	auto b_out = new BOSWrapper(&out);

	// header
	b_out->append(file_version
		)->append_c(0x0A
		)->append(header_size
		)->append(vertex_size
		)->append(face_size
		)->append(vertex_amount
		)->append(face_amount
		);

	auto tangent = MESHTangent::get_default();
	auto color3a = Color3a::get_default();
	
	// vertex set
	for (auto current = faces->get_head(); 
		current != nullptr; 
		current = current->get_next()) {
		auto value = current->get_value();

		for (uint8_t i = 0; i < 3; i++) {
			auto vertex = value->get_vertex(i),
				normal = value->get_normal(i);
			auto texture = value->get_texture(i);

			b_out->append(vertex->x()
				)->append(vertex->y()
				)->append(vertex->z()
				
				)->append(normal->x()
				)->append(normal->y()
				)->append(normal->z()
				
				)->append(texture->x()
				)->append(texture->y()
				
				)->append(tangent->x()
				)->append(tangent->y()
				)->append(tangent->z()
				)->append(tangent->x()
				
				)->append(color3a->r()
				)->append(color3a->g()
				)->append(color3a->b()
				)->append(color3a->a()
				);
		}
	}
	
	// face set
	for (uint32_t i = 0; i < vertex_amount; i++)
		b_out->append(i);
	

	delete b_out;
};
