#pragma once
#include <vulkan/vulkan_core.h>
#include <vk_mem_alloc.h>
#include "pipeline.h"

class VulkanMesh
{
public:
    void create(VmaAllocator allocator);
    void destroy(VmaAllocator allocator);

    VkBuffer getVertexBuffer() const { return vertexBuffer; }
    uint32_t getVertexCount()  const { return vertexCount; }

private:
    VkBuffer      vertexBuffer     = VK_NULL_HANDLE;
    VmaAllocation vertexAllocation = VK_NULL_HANDLE;
    uint32_t      vertexCount      = 0;
};
