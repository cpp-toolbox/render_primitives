These files need to be refactored, the cost of building new drawables is ever increasing due to inheritance, also rename this submodule, here are the details on how to refactor: 

To make the `MeshBufferingSystem` flexible so it conditionally uses the `IndexedVertexComponent` only if the entity has it, while still supporting entities that only use raw vertex data, we can adjust the logic to check whether an entity has the `IndexedVertexComponent`. If it doesn’t, we fall back on using only vertex data for drawing.

Here’s how we can implement that:

### Updated Systems

**MeshBufferingSystem**: 

We now check for both `IndexedVertexComponent` and `NormalsComponent`, buffering accordingly if the components exist. If an entity doesn’t have `IndexedVertexComponent`, it simply buffers vertex data without indices.

```cpp
void MeshBufferingSystem(EntityManager& entity_manager) {
    auto entities = entity_manager.get_entities_with_components<DrawableComponent>();

    for (auto& entity : entities) {
        auto& drawable = entity.get_component<DrawableComponent>();

        // Generate vertex buffer
        unsigned int vbo;
        glGenBuffers(1, &vbo);

        // Indexed or non-indexed vertex data?
        unsigned int ebo = 0;  // Element Buffer Object for indices, if needed
        bool has_indexed_component = entity.has_component<IndexedVertexComponent>();

        if (has_indexed_component) {
            glGenBuffers(1, &ebo);
        }

        // Normal buffer
        unsigned int nbo = 0;  // Normals Buffer Object
        bool has_normals = entity.has_component<NormalsComponent>();
        if (has_normals) {
            nbo = glGenBuffer();
        }

        // Bind VAO
        glBindVertexArray(drawable.vao);

        // Buffer vertex data (whether indexed or not)
        if (has_indexed_component) {
            auto& mesh = entity.get_component<IndexedVertexComponent>();

            // Bind and buffer vertex data
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(float), mesh.vertices.data(), GL_STATIC_DRAW);

            // Bind and buffer index data
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);
        }

        // Setup vertex attribute pointers for positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // If normals are available, bind and buffer normal data
        if (has_normals) {
            auto& normals = entity.get_component<NormalsComponent>();
            glBindBuffer(GL_ARRAY_BUFFER, nbo);
            glBufferData(GL_ARRAY_BUFFER, normals.normals.size() * sizeof(float), normals.normals.data(), GL_STATIC_DRAW);

            // Setup normal attribute pointers
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
        }
    }
}
```

**RenderSystem**: Now the system checks if the entity has the `IndexedVertexComponent` to determine whether to use indexed drawing (`glDrawElements`) or non-indexed drawing (`glDrawArrays`).

```cpp
void RenderSystem(EntityManager& entity_manager) {
    auto entities = entity_manager.get_entities_with_components<DrawableComponent>();

    for (auto& entity : entities) {
        auto& drawable = entity.get_component<DrawableComponent>();

        // Bind VAO for the entity
        glBindVertexArray(drawable.vao);

        // Check if the entity has an IndexedVertexComponent
        if (entity.has_component<IndexedVertexComponent>()) {
            auto& mesh = entity.get_component<IndexedVertexComponent>();

            // Use indexed drawing
            glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        } else {
            // If no IndexedVertexComponent, use non-indexed drawing
            glDrawArrays(GL_TRIANGLES, 0, 6);  // Assuming 6 vertices for example
        }
    }
}
```

### Components

No changes are needed in the components, as they remain focused on holding data.

**DrawableComponent**:

```cpp
struct DrawableComponent {
    unsigned int vao; // Vertex Array Object

    DrawableComponent() {
        glGenVertexArrays(1, &vao);
    }

    ~DrawableComponent() {
        glDeleteVertexArrays(1, &vao);
    }
};
```

**IndexedVertexComponent** (for indexed vertex data):

```cpp
struct IndexedVertexComponent {
    std::vector<float> vertices;    // Vertex data
    std::vector<unsigned int> indices; // Index data (optional)

    IndexedVertexComponent(const std::vector<float>& vertex_data, const std::vector<unsigned int>& index_data = {})
        : vertices(vertex_data), indices(index_data) {}
};
```

**NormalsComponent** (for normals data):

```cpp
struct NormalsComponent {
    std::vector<float> normals;  // Normal data

    NormalsComponent(const std::vector<float>& normal_data)
        : normals(normal_data) {}
};
```

### Example Usage

**Creating Entities**: Now you can create entities with or without indexed vertices, and the system will automatically handle them accordingly.

**Entity with Indexed Vertices and Normals**:

```cpp
std::vector<float> vertices = {
    // Vertex positions
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

std::vector<unsigned int> indices = { 0, 1, 2 };

// Normals
std::vector<float> normals = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

// Create an entity with indexed vertices and normals
Entity entity = entity_manager.create_entity();
entity.add_component<DrawableComponent>();  
entity.add_component<IndexedVertexComponent>(vertices, indices);
entity.add_component<NormalsComponent>(normals);
```

**Entity with Non-Indexed Vertices and No Normals**:

```cpp
std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

// Create an entity with only vertex data
Entity entity = entity_manager.create_entity();
entity.add_component<DrawableComponent>();  
entity.add_component<IndexedVertexComponent>(vertices);  // No indices, non-indexed draw
```

### Running Systems

```cpp
MeshBufferingSystem(entity_manager);
RenderSystem(entity_manager);
```

### Summary of Changes

1. **MeshBufferingSystem**: Now checks if the entity has an `IndexedVertexComponent`. If it does, it buffers the vertex and index data. If it only has vertex data, it buffers the vertices without using an element buffer.
2. **RenderSystem**: Now conditionally draws entities using `glDrawElements` (for indexed vertices) or `glDrawArrays` (for non-indexed vertices).
3. **Entity Creation**: Entities can now be created with or without indexed vertex data, making the system more flexible.

This setup maintains the ECS principle of separating data and logic, while supporting both indexed and non-indexed entities in the rendering pipeline.
