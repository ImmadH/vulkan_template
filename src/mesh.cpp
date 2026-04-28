#include "mesh.h"
#include <cstring>
#include <stdexcept>
#include <vector>
#include <iostream>

void VulkanMesh::create(VmaAllocator allocator)
{
    const std::vector<Vertex> vertices = {
        {{ 0.0f, -0.5f}, {1, 0, 0}},
        {{ 0.5f,  0.5f}, {0, 1, 0}},
        {{-0.5f,  0.5f}, {0, 0, 1}}
    };
    vertexCount = (uint32_t)vertices.size();

    VkBufferCreateInfo bufInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    bufInfo.size  = sizeof(Vertex) * vertices.size();
    bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

    VmaAllocationCreateInfo allocInfo{};
    allocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    if (vmaCreateBuffer(allocator, &bufInfo, &allocInfo, &vertexBuffer, &vertexAllocation, nullptr) != VK_SUCCESS)
        throw std::runtime_error("failed to create vertex buffer!");

    void* data;
    vmaMapMemory(allocator, vertexAllocation, &data);
    memcpy(data, vertices.data(), (size_t)bufInfo.size);
    vmaUnmapMemory(allocator, vertexAllocation);

    std::cout << "Created Vertex Buffer\n";
}

void VulkanMesh::destroy(VmaAllocator allocator)
{
    if (vertexBuffer)
    {
        vmaDestroyBuffer(allocator, vertexBuffer, vertexAllocation);
        vertexBuffer     = VK_NULL_HANDLE;
        vertexAllocation = VK_NULL_HANDLE;
    }
    std::cerr << "Vertex Buffer Destroyed\n";
}
