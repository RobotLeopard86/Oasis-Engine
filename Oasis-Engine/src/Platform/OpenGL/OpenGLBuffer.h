#pragma once

#include "OasisEngine/Rendering/Buffer.h"

namespace Oasis {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& newLayout) override { layout = newLayout; };
		const BufferLayout& GetLayout() const override { return layout; }
	private:
		uint32_t renderId;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override;
	private:
		uint32_t renderId;
		uint32_t indexCount;
	};
}