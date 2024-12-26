import * as THREE from "three";
import { loadShaders } from "./shader";
import GUI from "lil-gui";

let scene: THREE.Scene;
let camera: THREE.PerspectiveCamera;
let renderer: THREE.WebGLRenderer;
let plane: THREE.Mesh;
let material: THREE.ShaderMaterial;

// zoom & controls
const ZOOM_SPEED = 0.1;

const mousePos = { x: 0.0, y: 0.0 };
const prevCenter = { x: 0.0, y: 0.0 };
let drag = false;

// settings
let width = window.innerWidth;
let height = window.innerHeight;
const settings = {
  zoom: 1.0,
  maxIter: 50,
  // Center
  centerX: 0.3,
  centerY: 0.05,
  // Julia Constant
  juliaX: -0.4,
  juliaY: 0.6,
  // Colors
  darkRed: new THREE.Vector3(170, 0, 0),
  amber: new THREE.Vector3(255, 255, 140),
};

const init = async () => {
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);

  renderer = new THREE.WebGLRenderer();
  renderer.setSize(width, height);
  renderer.domElement.style.cursor = "grab";
  document.body.appendChild(renderer.domElement);

  const geometry = new THREE.PlaneGeometry(2, 2);
  const shaders = await loadShaders(
    "/shaders/shader.vert",
    "/shaders/shader.frag",
  );
  material = new THREE.ShaderMaterial({
    uniforms: {
      zoom: { value: settings.zoom },
      center: { value: new THREE.Vector2(settings.centerX, settings.centerY) },
      maxIter: { value: settings.maxIter },
      juliaConstant: {
        value: new THREE.Vector2(settings.juliaX, settings.juliaY),
      },
      darkRed: { value: settings.darkRed },
      amber: { value: settings.amber },
    },
    vertexShader: shaders.vertex_shader,
    fragmentShader: shaders.fragment_shader,
  });
  plane = new THREE.Mesh(geometry, material);
  scene.add(plane);

  camera.position.z = 1;

  // Setup lilGUI for setting controls
  const panel = new GUI();
  panel.add(settings, "maxIter", 1, 100);
  panel.add(settings, "zoom", 1, 10000).listen();

  const folder1 = panel.addFolder("Center");
  folder1.add(settings, "centerX", -2.0, 2.0).listen();
  folder1.add(settings, "centerY", -2.0, 2.0).listen();

  const folder2 = panel.addFolder("Julia Constant");
  folder2.add(settings, "juliaX", -2.0, 2.0);
  folder2.add(settings, "juliaY", -2.0, 2.0);

  renderer.setAnimationLoop(animate);
};

const animate = () => {
  material.uniforms.zoom.value = settings.zoom;
  material.uniforms.maxIter.value = settings.maxIter;
  material.uniforms.juliaConstant.value = new THREE.Vector2(
    settings.juliaX,
    settings.juliaY,
  );
  material.uniforms.center.value = new THREE.Vector2(
    settings.centerX,
    settings.centerY,
  );

  renderer.render(scene, camera);
};

const onWindowResize = () => {
  // update width & height
  width = window.innerWidth;
  height = window.innerHeight;
  camera.aspect = width / height;
  camera.updateProjectionMatrix();
  renderer.setSize(width, height);
};

const onMouseScroll = (e: WheelEvent) => {
  let scrollZoom = -e.deltaY / 50;
  settings.zoom *= Math.exp(scrollZoom * ZOOM_SPEED);
};

const onMouseMove = (e: MouseEvent) => {
  if (drag) {
    let normalizedX = (-(e.clientX / width - 0.5) * 2 * 5) / settings.zoom;
    let normalizedY = ((e.clientY / height - 0.5) * 2 * 2) / settings.zoom;
    // change center cooridnates: (-2.0, 2.0)
    settings.centerX = Math.min(
      Math.max(prevCenter.x + (normalizedX - mousePos.x), -2.0),
      2.0,
    );
    settings.centerY = Math.min(
      Math.max(prevCenter.y + (normalizedY - mousePos.y), -2.0),
      2.0,
    );
  }
};

const onMouseDown = (e: MouseEvent) => {
  drag = true;
  let normalizedX = (-(e.clientX / width - 0.5) * 2 * 5) / settings.zoom;
  let normalizedY = ((e.clientY / height - 0.5) * 2 * 2) / settings.zoom;
  mousePos.y = normalizedY;
  mousePos.x = normalizedX;
  prevCenter.x = settings.centerX;
  prevCenter.y = settings.centerY;

  renderer.domElement.style.cursor = "grabbing";
};
const onMouseUp = () => {
  drag = false;
  renderer.domElement.style.cursor = "grab";
};

// Add listeners for user interaction
window.addEventListener("resize", onWindowResize);
window.addEventListener("wheel", onMouseScroll);
window.addEventListener("mousemove", onMouseMove);
window.addEventListener("mousedown", onMouseDown);
window.addEventListener("mouseup", onMouseUp);

init();
