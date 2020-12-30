#include <blah/graphics/shader.h>
#include <blah/internal/graphics_backend.h>

using namespace Blah;

ShaderRef Shader::create(const ShaderData* data)
{
	// get the shader
	auto shader = GraphicsBackend::create_shader(data);
	
	// validate the shader
	if (shader)
	{
		auto& uniforms = shader->uniforms();

		// make sure its uniforms are valid
		for (auto& it : uniforms)
			if (it.type == UniformType::None)
			{
				BLAH_ERROR_FMT("Uniform '%s' has an invalid type!\n\tOnly Float/Float2/Float3/Float4/Mat3x2/Mat4x4/Texture are allowed!", it.name.cstr());
				return ShaderRef();
			}

		// make sure uniform names don't overlap
		for (int i = 0; i < uniforms.size(); i ++)
			for (int j = i + 1; j < uniforms.size(); j ++)
				if (uniforms[i].name == uniforms[j].name)
				{
					BLAH_ERROR_FMT("Shader Uniform names '%s' overlap! All Names must be unique.", uniforms[0].name.cstr());
					return ShaderRef();
				}
	}

	return shader;
}