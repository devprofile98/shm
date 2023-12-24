#include "Mesh.hpp"
#include "Logger.hpp"

Mesh::Mesh(std::vector<Vertex> vertices1, std::vector<uint32_t> indices1, std::vector<Texture_INT> textures1, Material_INT mat)
    : vertices(vertices1), indices(indices1), textures(textures1), mat(mat) {

    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));

    glBindVertexArray(0);
}

void Mesh::Draw(std::shared_ptr<shader> shader_obj, const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation,
                float rotaion_degree, bool selected, shader *border_shader) {
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    shader_obj->use();
    shader_obj->setInt("skybox", 1);
    // SHM::Logger::error("this is the location for skybox {} {}", glGetUniformLocation(shader_obj->ID, "skybox"),
    //                    glGetUniformLocation(shader_obj->ID, "texture_diffuse1"));
    glm::mat4 model{1.0f};
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotaion_degree), rotation);
    shader_obj->setMat4("model", model);

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + (int)textures[i].bounded_slot); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader_obj->ID, (name + number).c_str()), (int)textures[i].bounded_slot);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // binding the skybox texture if the object is reflectable
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 1);

    shader_obj->setVec4("kd", mat.kd);
    if (mat.should_draw) {
        shader_obj->setInt("has_material", 1);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

    // always good practice to set everything back to defaults once configured.
    // glBindTexture(GL_TEXTURE_2D, 0);
}
