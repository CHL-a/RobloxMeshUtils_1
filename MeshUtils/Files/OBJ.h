#ifndef OBJ_H
#define OBJ_H

#include "MeshFile.h"

class OBJFace: public MeshFileFace{

	public: 
		using MeshFileFace::MeshFileFace;
		std::string to_line()const;
};

// OBJ
class OBJ: public MeshFile<OBJFace> {
	protected:
		class OBJCompressionNode{
			public:
				OBJFace *face;
				OBJ *referral;
				Vector3 *vertices[3];
				Vector3 *normals[3];
				Vector2 *textures[3];
				OBJCompressionNode *next;

				OBJCompressionNode(OBJ *referral, OBJFace *face);
				OBJCompressionNode(
					OBJ *referral,
					OBJFace *face, 
					OBJCompressionNode *next
				);

				~OBJCompressionNode();

				OBJCompressionNode* get_next(const uint32_t &ahead);
		};
	
	private:
		string* peek_prefix(std::istream &input)const;

		bool parse_line(
			std::istream &input,
			LinkedList<Vector3> *vertices,
			LinkedList<Vector3> *normals,
			LinkedList<Vector2> *textures
			);
		bool parse_face(std::istream &input);

	public:
		OBJ();
		OBJ(std::istream &input);

		void write_out(std::ostream &output) const override;
		void compress();
};


#endif