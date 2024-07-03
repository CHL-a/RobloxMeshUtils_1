#include "MeshFile.h"

//############################################################
// MeshDataCollection
//############################################################

inline Vector3* MeshDataCollection::get_vertex(uint32_t i)
	const{return vertices->at(i);};

inline Vector3* MeshDataCollection::get_normal(uint32_t i)
	const{return normals->at(i);};

inline Vector2* MeshDataCollection::get_texture(uint32_t i)
	const{return textures->at(i);};

inline uint32_t MeshDataCollection::get_vertices_size() const{
	return vertices->size();};

inline uint32_t MeshDataCollection::get_normals_size() const{
	return normals->size();};

inline uint32_t MeshDataCollection::get_textures_size() const{
	return textures->size();};
	
//############################################################
// MeshFileFace
//############################################################

// STATICS
inline uint32_t MeshFileFace::default_indices[3] = {0,0,0};

inline bool MeshFileFace::in_bounds_3(uint8_t i){
	return i>=0 && i<=2;}

inline bool MeshFileFace::check_bounds_3(uint8_t i){
	bool result = in_bounds_3(i);

	if (!result) {
		cerr << "Attempting to use out bounds: expected"
			<< " i in [0,2], got " 
			<< i;
	}

	return result;
};

// CONSTRUCTORS
inline MeshFileFace::MeshFileFace(
	MeshDataCollection* referral,
	uint32_t vertices[3],
	uint32_t normals[3],
	uint32_t textures[3]
){__init(referral, vertices, normals, textures);};

inline MeshFileFace::MeshFileFace(
	MeshDataCollection* referral,
	uint32_t vertices[3],
	uint32_t normals[3]
	): MeshFileFace(
		referral,
		vertices, 
		normals,
		default_indices){};

inline MeshFileFace::MeshFileFace(
	MeshDataCollection* referral,
	uint32_t vertices[3]
	): MeshFileFace(referral, vertices, default_indices) {};

inline MeshFileFace::MeshFileFace(MeshFileFace &self): 
	MeshFileFace(
		self.referral,
		self.vertices, 
		self.normals, 
		self.textures
	) {}

// DESTRUCTORS
/**
 * Only dereferences
*/
inline MeshFileFace::~MeshFileFace(){detatch();}

// METHODS
inline void MeshFileFace::__init(
	MeshDataCollection* referral,
	uint32_t vertices[3],
	uint32_t normals[3],
	uint32_t textures[3]){
	this->referral = referral;
	set_vertices(vertices);
	set_normals(normals);
	set_textures(textures);
};

inline void MeshFileFace::detatch(){referral = nullptr;}

inline Vector3* MeshFileFace::get_vertex(uint8_t i)const{
	return !check_bounds_3(i) 
		? nullptr 
		: referral->get_vertex(vertices[i] - 1);
};

/**
 * Returns a normal vector of a vertex. If none are availiable,
 * then it is calculated by the other vertices
 */
inline Vector3* MeshFileFace::get_normal(uint8_t i)const{
	if (!check_bounds_3(i))
		return nullptr;
	if (normals[i] != 0)
		return referral->get_normal(normals[i] - 1);

	Vector3 *result = new Vector3((*get_vertex(0)-*get_vertex(1))
		.cross(*get_vertex(1)-*get_vertex(2))
		.get_unit());

	return result;
};

/**
 * Returns a Vector2 in terms of UV. If not present then 
 * Vector2::yaxis
 * 
 */
inline Vector2* MeshFileFace::get_texture(uint8_t i)const{
	return !check_bounds_3(i) 
			? nullptr 
		: textures[i] != 0
			? referral->get_texture(textures[i]-1) 
			: &Vector2::yAxis;
};

inline void MeshFileFace::set_vertex(uint8_t i, uint32_t v){
	if (!check_bounds_3(i)) return;
	
	vertices[i] = v;
}

inline void MeshFileFace::set_normal(uint8_t i, uint32_t v){
	if (!check_bounds_3(i)) return;
	
	normals[i] = v;
}

inline void MeshFileFace::set_texture(uint8_t i, uint32_t v){
	if (!check_bounds_3(i)) return;
	
	textures[i] = v;
}

inline void MeshFileFace::set_vertices(uint32_t v[3]){
	for (uint8_t i = 0; i < 3; i++) vertices[i] = v[i];
}

inline void MeshFileFace::set_vertices(uint32_t *v[3]){
	set_vertices(*v);}

inline void MeshFileFace::set_normals(uint32_t n[3]){
	for (uint8_t i = 0; i < 3; i++) normals[i] = n[i];
};

inline void MeshFileFace::set_normals(uint32_t *n[3]){
	set_normals(*n);};

inline void MeshFileFace::set_textures(uint32_t t[3]){
	for (uint8_t i = 0; i < 3; i++) textures[i] = t[i];
};

inline void MeshFileFace::set_textures(uint32_t *t[3]){
	set_textures(*t);};

/**
 * Takes zero based parameter and returns a one based uint, 
 * 0 sigifies does not exist.
 */
inline uint32_t MeshFileFace::get_vertex_p(uint8_t i) const{
	return !check_bounds_3(i) ? 
		0 : 
		vertices[i];
};

/**
 * Takes zero based parameter and returns a one based uint, 
 * 0 sigifies does not exist.
 */
inline uint32_t MeshFileFace::get_normal_p(uint8_t i) const {
	return !check_bounds_3(i) ? 
		0 : 
		normals[i];
};


/**
 * Takes zero based parameter and returns a one based uint, 
 * 0 sigifies does not exist.
 */
inline uint32_t MeshFileFace::get_texture_p(uint8_t i) const {
	return !check_bounds_3(i) ? 
		0 : 
		textures[i];
};

//############################################################
// MeshFile
//############################################################

// CONSTRUCTORS
template<typename FACE>
MeshFile<FACE>::MeshFile() {__init();}

template<typename FACE>
MeshFile<FACE>::MeshFile(std::istream &input){};

// DESTRUCTORS
/**
 * Includes full destruction of all elements inside
*/
template<typename FACE>
MeshFile<FACE>::~MeshFile(){
	delete faces, vertices, normals, textures;
}

// METHODS
template<typename FACE>
void MeshFile<FACE>::__init(){
	is_constructed = true;
	faces = new LinkedList<FACE>();
}

template<typename FACE>
Node<FACE>* MeshFile<FACE>::get_face_head()const{
	return faces->get_head();
}