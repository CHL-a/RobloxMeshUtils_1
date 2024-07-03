#ifndef MESH_H
#define MESH_H

#include "OBJ.h"

class MESHTangent {
	protected: 
		int8_t _x, _y, _z, _s;
		static MESHTangent default_obj;

	public:
		MESHTangent(
			const int8_t &x0 = 0,
			const int8_t &y0 = 0,
			const int8_t &z0 = 0,
			const int8_t &s0 = 0
		);

		int8_t x()const;
		void x(const int8_t &alt);
		int8_t y()const;
		void y(const int8_t &alt);
		int8_t z()const;
		void z(const int8_t &alt);
		int8_t s()const;
		void s(const int8_t &alt);
		static MESHTangent* get_default();
};

class MESHFace: public MeshFileFace {
	public:
		using MeshFileFace::MeshFileFace;
};

class MESH: public MeshFile<MESHFace> {
	protected:
		uint16_t header_size;
		uint8_t vertex_size,
			face_size;

		static string file_version;
	
	public:
		MESH(OBJ *obj);

		void write_out(std::ostream &output) const override;
};

#endif