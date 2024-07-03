#ifndef MESHFILE_H
#define MESHFILE_H

#include <iostream>
#include "VectorNVector.h"
#include "LinkedList.h"

class MeshDataCollection {
	protected:
		VectorNVector<Vector3> *vertices = nullptr,
			*normals = nullptr;
		VectorNVector<Vector2> *textures = nullptr;

	public:
		Vector3* get_vertex(uint32_t i)const;
		Vector3* get_normal(uint32_t i)const;
		Vector2* get_texture(uint32_t i)const;
		uint32_t get_vertices_size()const;
		uint32_t get_normals_size()const;
		uint32_t get_textures_size()const;
};

/**
 * @class
 * Object responsible for holding all vertex, normal and texture structs.
 * 
 * Mind that this object is a one based system, while array access is 0-based, all values set and get are to be expected 1-based, 0 is considered non existant
*/
class MeshFileFace{
	protected:
		uint32_t vertices[3];
		uint32_t normals[3];
		uint32_t textures[3];
		MeshDataCollection *referral;
		static uint32_t default_indices[3];
		
		void set_vertices(uint32_t *vertices[3]);
		void set_vertices(uint32_t vertices[3]);
		void set_normals(uint32_t *normals[3]);
		void set_normals(uint32_t normals[3]);
		void set_textures(uint32_t *textures[3]);
		void set_textures(uint32_t textures[3]);

		void __init(
			MeshDataCollection *referral,
			uint32_t vertices[3],
			uint32_t normals[3],
			uint32_t textures[3]
		);
	
	public:
		MeshFileFace(MeshFileFace &self);
		MeshFileFace(
			MeshDataCollection *referral,
			uint32_t vertices[3],
			uint32_t normals[3],
			uint32_t textures[3]
		);
		MeshFileFace(
			MeshDataCollection *referral,
			uint32_t vertices[3],
			uint32_t normals[3]
		);
		MeshFileFace(
			MeshDataCollection *referral,
			uint32_t vertices[3]
		);
		
		~MeshFileFace();

		void detatch();
		uint32_t get_vertex_p(uint8_t i) const;
		uint32_t get_normal_p(uint8_t i) const;
		uint32_t get_texture_p(uint8_t i) const;
		
		Vector3* get_vertex(uint8_t i)const;
		Vector3* get_normal(uint8_t i)const;
		Vector2* get_texture(uint8_t i)const;

		void set_vertex(uint8_t i, uint32_t v);
		void set_normal(uint8_t i, uint32_t v);
		void set_texture(uint8_t i, uint32_t v);

		static bool in_bounds_3(uint8_t i);
		static bool check_bounds_3(uint8_t i);
};

template <typename FACE>
class MeshFile: public MeshDataCollection {
	static_assert(
		std::is_base_of<MeshFileFace, FACE>::value,
		"FACE must be derived from MeshFileFace "
	);
	protected:
		LinkedList<FACE> *faces;
		bool is_constructed;

	public:
		MeshFile();
		MeshFile(std::istream &input);

		virtual ~MeshFile();

		Node<FACE>* get_face_head()const;
		virtual void __init();
		virtual void write_out(std::ostream &output) const = 0;
};

#include "MeshFile.tpp"

#endif