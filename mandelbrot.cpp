#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>          



//image resolution and initial windows size
const int IMAGE_WIDTH = 500;
const int IMAGE_HEIGHT = 300;

double aspect_ratio = double(IMAGE_WIDTH) / double(IMAGE_HEIGHT);

double y_mandelbrot_size = 3.;
double x_mandelbrot_size = y_mandelbrot_size * aspect_ratio;


double oldsize;
double zoom = 1.0;
double yorigin = -1.5;
double xorigin = yorigin * aspect_ratio;
int maxiter = 800;

sf::Color getColor(int);

int samples_per_pixel = 4;



enum COLORMAP
{
	COLORMAP_1 = 1,
	COLORMAP_2 = 2,
};

//by default COLORMAP_1
COLORMAP active_colormap = COLORMAP_1;


inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}


int main() {

	//==============================================================================================
	// Keyboard support and event handling
	//==============================================================================================

	sf::RenderWindow window(sf::VideoMode(IMAGE_WIDTH, IMAGE_HEIGHT), "Mandelbrot");
	window.setFramerateLimit(30);

	sf::Image image;
	image.create(IMAGE_WIDTH, IMAGE_HEIGHT, sf::Color(0, 0, 0));
	sf::Texture texture;
	sf::Sprite sprite;

	bool stateChanged = true; // track whether the image needs to be regenerated

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case  sf::Event::Resized: {
				aspect_ratio = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);

			}
			case sf::Event::KeyPressed:
				stateChanged = true; // image needs to be recreated when the user changes zoom or offset
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Q:
					oldsize = x_mandelbrot_size;
					x_mandelbrot_size *= 0.6;
					xorigin += (oldsize - x_mandelbrot_size) * 0.5;
					oldsize = y_mandelbrot_size;
					y_mandelbrot_size *= 0.6;
					yorigin += (oldsize - y_mandelbrot_size) * 0.5;
					zoom *= 0.6;
					break;
				case sf::Keyboard::E:
					oldsize = x_mandelbrot_size;
					x_mandelbrot_size /= 0.6;
					xorigin += (oldsize - x_mandelbrot_size) * 0.5;
					oldsize = y_mandelbrot_size;
					y_mandelbrot_size /= 0.6;
					yorigin += (oldsize - y_mandelbrot_size) * 0.5;
					zoom /= 0.6;
					break;
				case sf::Keyboard::Z:   // increases max iterations
					maxiter += 200;
					break;
				case sf::Keyboard::X:    // decreases max iterations
					if (maxiter > 200)
						maxiter -= 200;
					break;
				case sf::Keyboard::W: // move up
					yorigin -= 0.2 * zoom;
					break;
				case sf::Keyboard::S: // move down
					yorigin += 0.2 * zoom;
					break;
				case sf::Keyboard::A: // move left
					xorigin -= 0.2 * zoom;
					break;
				case sf::Keyboard::D: // move right
					xorigin += 0.2 * zoom;
					break;
				case sf::Keyboard::V: // increases samples per pixel
					samples_per_pixel++;
					break;
				case sf::Keyboard::C: // decreases samples per pixel
					if (samples_per_pixel > 1)
						samples_per_pixel--;
					break;

				case sf::Keyboard::Num1: // COLORMAP 1 
					active_colormap = COLORMAP_1;
					break;

				case sf::Keyboard::Num2: // COLORMAP 2 
					active_colormap = COLORMAP_2;
					break;

				default: break;
				}
			default:
				break;
			}
		}

		if (stateChanged)
		{

			//==============================================================================================
			// Computing Mandelbrot Set
			//==============================================================================================

			double xstep = x_mandelbrot_size / IMAGE_WIDTH;
			double ystep = y_mandelbrot_size / IMAGE_HEIGHT;

			double x = xorigin;
			double y = yorigin;

			for (int j = 0; j < IMAGE_HEIGHT; ++j)
			{
				x = xorigin;
				for (int i = 0; i < IMAGE_WIDTH; ++i)
				{

					int r_ = 0;
					int g_ = 0;
					int b_ = 0;


					for (int s = 0; s < samples_per_pixel; ++s)
					{
						double a = 0, b = 0;
						int n = 0;

						//antialiasing
						double dx = (random_double()) * xStep;
						double dy = (random_double()) * yStep;

						do
						{

							double tmp = a;
							a = a * a - b * b + x + dx;
							b = 2 * tmp * b + y + dy;
							n++;

						} while ((n < maxiter) && (a * a + b * b <= 4));

						sf::Color col = getColor(n);
						r_ += (int)col.r;
						g_ += (int)col.g;
						b_ += (int)col.b;

					}


					image.setPixel(i, j, sf::Color((sf::Uint8)round(double(r_) / samples_per_pixel),
						(sf::Uint8)round(double(g_) / samples_per_pixel),
						(sf::Uint8)round(double(b_) / samples_per_pixel)));


					x += xstep;
				}
				y += ystep;
			}

			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}

		window.clear();
		window.draw(sprite);
		window.display();

		stateChanged = false;
	}

	return 0;
}


sf::Color getColor(const int iterations)
{
	sf::Uint8 r = 0, g = 0, b = 0;

	//==============================================================================================
	// Coloring Mandelbrot Set
	//==============================================================================================


	sf::Uint8 grad = iterations % 200;


	switch (active_colormap) {

	case COLORMAP_1:
		if (iterations == maxiter)
		{
			r = 0;
			g = 0;
			b = 0;
		}
		else if (grad < 50)
		{

			r = 42 + (sf::Uint8)((255.0 - 42.0) / 50.0) * grad;
			g = 13 + (sf::Uint8)((255.0 - 13.0) / 50.0) * grad;
			b = 126 + (sf::Uint8)((255.0 - 126.0) / 50.0) * grad;

		}
		else if (grad < 100)
		{
			grad = grad - 50;
			r = 255 + (sf::Uint8)((198. - 255.) / 50.0) * grad;
			g = 255 + (sf::Uint8)((112. - 255.) / 50.0) * grad;
			b = 255 + (sf::Uint8)((19. - 255.) / 50.0) * grad;
		}
		else if (grad < 150)
		{

			grad = grad - 100;

			r = 198 + (sf::Uint8)((0. - 198.) / 50.0) * grad;
			g = 112 + (sf::Uint8)((0. - 112.) / 50.0) * grad;
			b = 19 + (sf::Uint8)((0. - 19.) / 50.0) * grad;

		}
		else if (iterations >= maxiter - 50)
		{
			grad = grad - 150;
			r = 198 + (sf::Uint8)((0. - 0.) / 50.0) * grad;
			g = 112 + (sf::Uint8)((0. - 0.) / 50.0) * grad;
			b = 19 + (sf::Uint8)((0. - 0.) / 50.0) * grad;
		}
		else
		{

			grad = grad - 150;
			r = 0 + (sf::Uint8)((42. - 0.) / 50.0) * grad;
			g = 0 + (sf::Uint8)((13. - 0.) / 50.0) * grad;
			b = 0 + (sf::Uint8)((126. - 0.) / 50.0) * grad;
		}
		break;



	case COLORMAP_2:
		if (iterations == maxiter)
		{
			r = 0;
			g = 0;
			b = 0;
		}
		else if (grad < 50)
		{

			r = 5 + (sf::Uint8)((66. - 5.) / 50.0) * grad;
			g = 5 + (sf::Uint8)((12. - 5.) / 50.0) * grad;
			b = 16 + (sf::Uint8)((81. - 16.) / 50.0) * grad;

		}
		else if (grad < 100)
		{
			grad = grad - 50;
			r = 66 + (sf::Uint8)((192. - 66.) / 50.0) * grad;
			g = 12 + (sf::Uint8)((74. - 12.) / 50.0) * grad;
			b = 81 + (sf::Uint8)((44. - 81.) / 50.0) * grad;
		}
		else if (grad < 150)
		{

			grad = grad - 100;

			r = 192 + (sf::Uint8)((255. - 192.) / 50.0) * grad;
			g = 74 + (sf::Uint8)((222. - 74.) / 50.0) * grad;
			b = 44 + (sf::Uint8)((64. - 44.) / 50.0) * grad;

		}
		else if (iterations >= maxiter - 50)
		{
			grad = grad - 150;
			r = 255 + (sf::Uint8)((0. - 255.) / 50.0) * grad;
			g = 222 + (sf::Uint8)((0. - 222.) / 50.0) * grad;
			b = 64 + (sf::Uint8)((0. - 64.) / 50.0) * grad;
		}
		else
		{

			grad = grad - 150;
			r = 255 + (sf::Uint8)((5. - 255.) / 50.0) * grad;
			g = 222 + (sf::Uint8)((5. - 222.) / 50.0) * grad;
			b = 64 + (sf::Uint8)((16. - 64.) / 50.0) * grad;
		}
		break;


	}

	return sf::Color(r, g, b);
}
