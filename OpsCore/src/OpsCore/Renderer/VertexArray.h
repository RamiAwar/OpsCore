#pragma once
#include "ocpch.h"

#include "OpsCore/Renderer/Buffer.h"

namespace oc {


	class VertexArray {
		
	public: 
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

		static VertexArray* Create();
	};

}