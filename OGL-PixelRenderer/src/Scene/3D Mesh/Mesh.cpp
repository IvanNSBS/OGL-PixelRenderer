#include "Mesh.h"


Mesh::Mesh (
	const std::vector<Vertex>& verts, 
	const std::vector<unsigned int>& idxs, 
	const std::vector<Texture>& texs) : vertices(verts), indices(idxs), textures(texs) 
{
	SetupMesh();
}

Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<GLuint>& idxs) : vertices(verts) {
    SetupMesh();
}
Mesh::Mesh(const std::vector<Vertex>& verts, const std::vector<GLuint>& idxs, Material* mat) : vertices(verts), indices(idxs) {
    material = mat;
    SetupMesh();
}


Mesh::~Mesh() {
    //glDeleteVertexArrays(1, &_VAO);
    //glDeleteBuffers(1, &_VBO);
    //glDeleteBuffers(1, &_EBO);
}

void Mesh::SetupMesh() {
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // vertex texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texUv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void Mesh::SetMaterial(Material* mat) { material = mat; }


void Mesh::Draw() {
    if (!material) {
        std::cout << "ERROR::NO_MATERIAL_ATTACHED_TO_MESH::CAN'T_DRAW\n";
        return;
    }

    material->Use();

    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}

void Mesh::BeginProperty() {
    if (!material)
        return;

    material->BeginProperty();
}