export const loadShaders = async (
  vertexShaderPath: string,
  fragmentShaderPath: string,
) => {
  const vertexShader = await readFile(vertexShaderPath);
  const fragmentShader = await readFile(fragmentShaderPath);

  return {
    vertex_shader: vertexShader,
    fragment_shader: fragmentShader,
  };
};

const readFile = async (path: string) => {
  const response = await fetch(path);
  if (!response.ok) {
    throw new Error(`Failed to load file at ${path}`);
  }
  const text = await response.text();
  return text;
};
