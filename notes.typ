#set document(title: "Mandelbrot Set")
#set quote(block: true)

#title()

= Preface

The following are notes on my attempt on rendering the Mandelbrot set with high precision.

= The Mandelbrot set

The Mandelbrot set's definition can be written in multiple ways.

#quote(
  attribution: [#link(
    "https://mathr.co.uk/mandelbrot/perturbation.pdf",
    "Perturbation techniques applied to the Mandelbrot set",
  )],
)[
  Consider iterations of a quadratic polynomial $F$ over complex numbers:
  $
    F(z, c) = z^2 + c
    F^(n+1) (z, c) = F(F^n (z, c), c)
  $
  The Mandelbrot set $M$ is the set of $c in CC$ for which the iterates of $z = 0$ remain bounded:
  $
    M = {c in CC colon F^n (0, c) arrow.not infinity "as" n arrow infinity}
  $
]



= Visualizing the Mandelbrot set

Despite its simple formula, visualizing the Mandelbrot set requires more techniques than simple brute-forcing, the further we zoom into the fractal.

== Naive implementation

A naive attempt of visualizing the Mandelbrot set can look like this:
```glsl
vec2 mult(vec2 v1, vec2 v2) {
    return vec2(
        v1.x * v2.x - v1.y * v2.y, // Real part
        v1.x * v2.y + v1.y * v2.x // Imaginary part
    );
}

float compute_iterations(vec2 c) {
    const float B = 256.0f;
    float n = 0.0f;
    vec2 z = vec2(0.0f);

    for (int i = 0; i < max_iter; i++) {
        z = mult(z, z) + c;
        if (dot(z, z) > B * B) break;
        n += 1.0f;
    }

    // Smooth iteration count
    float sn = n - log2(log2(dot(z,z))) + 4.0;
    return sn;
}
```
where `sn` can be used to assign a specific color to the corresponding value of $c$.

However, if we try to zoom in too far the limitation on floating point precision is quite apparent.

#figure(
  image("pictures/float_limitation.png", width: 40%),
  caption: [Unclear render of a fractal due to imprecision of floating point numbers.],
)


== Perturbation techniques

The following explanation is adapted from #link("https://mathr.co.uk/blog/2021-05-14_deep_zoom_theory_and_practice.html#a2021-05-14_deep_zoom_theory_and_practice_3", "Deep zoom theory and practice") by Claude Heiland-Allen.


To mitigate this limitation, we must use higher precision floating point types for the calculation process. However, calculating the appropriate iteration count for each high precision floating point types is most likely too slow.

To speed up this process, we introduce perturbation techniques.

The core idea is quite simple. Since $z^2 + c$ is analytic, nearby points remain nearby under iteration.
Let upper case variables ($Z, C$) be the unperturbed reference (in high precision) and lower case variables ($z, c$) be the perturbed per pixel delta (in low precision).

Start with the iteration formula:
$
  Z arrow Z^2 + C
$

Perturb the variables:
$
  (Z+z) arrow (Z+z)^2 + (C + c) = (Z^2 + C) + (2Z z + z^2 + c) \
$

Then
$
  z arrow 2Z z + z^2 + c.
$

Using this, we can
