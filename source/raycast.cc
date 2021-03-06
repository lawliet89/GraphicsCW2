#include "raycast.h"

// Globals:

// File names
char *_inputName       = NULL;
char *_outputNameRGB   = NULL;
char *_outputNameDepth = NULL;

// Image parameters.
int _width      = 100;
int _height     = 100;
float _depthMin = 0;
float _depthMax = 1;

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &, Image &);

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &, Image &);

int main(int argc, char** argv) {

  int i;
  // sample command lines:
  // raycast -input input.txt -size 100 100 -output output.ppm
  // raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.ppm

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-input") == 0) {
      i++;assert (i < argc);
      _inputName = argv[i];
    } else if (strcmp(argv[i], "-size") == 0) {
      i++;assert (i < argc);
      _width = atoi(argv[i]);
      i++;assert (i < argc);
      _height = atoi(argv[i]);
    } else if (strcmp(argv[i], "-output") == 0) {
      i++;assert (i < argc);
      _outputNameRGB = argv[i];
    } else if (strcmp(argv[i], "-depth") == 0) {
      i++;assert (i < argc);
      _depthMin = atof(argv[i]);
      i++;assert (i < argc);
      _depthMax = atof(argv[i]);
      i++;assert (i < argc);
      _outputNameDepth = argv[i];
    } else {
      printf(
          "Error with command line argument %d: '%s'\n",
          i, argv[i]);
      assert(0);
    }
  }

  // Read in the scene description file, parsing the objects,
  // camera details, etc.
  SceneParser scene(_inputName);

  // Color and depth images.
  Image rgbImage(_width, _height);
  Image depthImage(_width, _height);

  // Do the rendering.
  renderRGBImage(scene, rgbImage);
  renderDepthImage(scene, depthImage);

  // Write results if necessary.
  if (_outputNameRGB != NULL) {
    rgbImage.SavePPM(_outputNameRGB);
  }

  if (_outputNameDepth != NULL){
    depthImage.SavePPM(_outputNameDepth);
  }

}

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &scene, Image &image) {

  // TODO: renderRGBImage
	// Objects in scene
	Group *objects = scene.getGroup();
	// Get the camera
	Camera *camera = scene.getCamera();
	// Get background colour
	Vec3f background = scene.getBackgroundColor();

	// Image width, and height
	int width = image.Width();
	int height = image.Height();

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			// Calculate x and y index
			float xIndex = ((float) x)/width;
			float yIndex = ((float) y)/height;

			// Get a ray from the camera
			Ray ray = camera -> generateRay(Vec2f(xIndex, yIndex));

			// Empty Hit object
			Hit hit;

			// Check for intersections
			bool intersect = objects -> intersect(ray, hit);

			// There is an intersection
			if (intersect){
				image.SetPixel(x,y, hit.getColor());
			}
			else{
				// Background colour
				image.SetPixel(x,y, background);
			}

		}
	}
}

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &scene, Image &image) {

  // TODO: renderDepthImage
	// Objects in scene
	Group *objects = scene.getGroup();
	// Get the camera
	Camera *camera = scene.getCamera();

	// Image width, and height
	int width = image.Width();
	int height = image.Height();

	// Useful values
	Vec3f black(0.f, 0.f, 0.f);
	float difference = _depthMax - _depthMin;

	for (int x = 0; x < width; x++){
		for (int y = 0; y < height; y++){
			// Calculate x and y index
			float xIndex = ((float) x)/width;
			float yIndex = ((float) y)/height;

			// Get a ray from the camera
			Ray ray = camera -> generateRay(Vec2f(xIndex, yIndex));

			// Empty Hit object
			Hit hit;

			// Check for intersections
			bool intersect = objects -> intersect(ray, hit);

			// There is an intersection
			if (intersect){
				float colour;
				float t = hit.getT();

				// Calculate colour
				if (t <= _depthMin)
					colour = 1.f;	// white
				else if (t >= _depthMax)
					colour = 0.f;	// black
				else{
					// Grey
					colour = (_depthMax - t)/difference;
				}

				image.SetPixel(x,y, Vec3f(colour, colour, colour));
			}
			else{
				// Black colour
				image.SetPixel(x,y, black);
			}

		}
	}
}
