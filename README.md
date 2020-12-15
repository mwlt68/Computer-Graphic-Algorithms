# Computer-Graphic-Algorithms
This repo for understand how can I work  with computer graphic. There are a lots of algorithm.

# Bézier Curves
Bézier curves are used a lot in computer graphics, often to produce smooth curves, and yet they are a very simple tool. If you have ever used Photoshop you might have stumbled upon that tool called “Anchor” where you can put anchor points and draw some curves with them… Yep, these are Bézier curves. Or if you have used vector-based graphic, SVG, these too use Bézier curves. Please visit below link for how it works.

https://towardsdatascience.com/b%C3%A9zier-curve-bfffdadea212

# What is Bresenham Line Generation
Link:https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/

Given coordinate of two points A(x1, y1) and B(x2, y2). The task to find all the intermediate points required for drawing line AB on the computer screen of pixels. Note that every pixel has integer coordinates.

Examples:

Input : A(0,0), B(4,4) Output : (0,0), (1,1), (2,2), (3,3), (4,4)

Input : A(0,0), B(4,2) Output : (0,0), (1,0), (2,1), (3,1), (4,2) Below are some assumptions to keep algorithm simple.

We draw line from left to right. x1 < x2 and y1< y2 Slope of the line is between 0 and 1. We draw a line from lower left to upper right. Let us understand the process by considering the naive way first.

// A naive way of drawing line void naiveDrawLine(x1, x2, y1, y2) { m = (y2 - y1)/(x2 - x1) for (x = x1; x <= x2; x++) {
// Assuming that the round function finds // closest integer to a given float. y = round(mx + c);
print(x, y); } } Above algorithm works, but it is slow. The idea of Bresenham’s algorithm is to avoid floating point multiplication and addition to compute mx + c, and then computing round value of (mx + c) in every step. In Bresenham’s algorithm, we move across the x-axis in unit intervals.

We always increase x by 1, and we choose about next y, whether we need to go to y+1 or remain on y. In other words, from any position (Xk, Yk) we need to choose between (Xk + 1, Yk) and (Xk + 1, Yk + 1).

We would like to pick the y value (among Yk + 1 and Yk) corresponding to a point that is closer to the original line. We need to a decision parameter to decide whether to pick Yk + 1 or Yk as next point. The idea is to keep track of slope error from previous increment to y. If the slope error becomes greater than 0.5, we know that the line has moved upwards one pixel, and that we must increment our y coordinate and readjust the error to represent the distance from the top of the new pixel – which is done by subtracting one from error.

// Modifying the naive way to use a parameter // to decide next y. void withDecisionParameter(x1, x2, y1, y2) { m = (y2 - y1)/(x2 - x1) slope_error = [Some Initial Value] for (x = x1, y = y1; x = 0.5)
{
y++;
slope_error -= 1.0;
} } How to avoid floating point arithmetic The above algorithm still includes floating point arithmetic. To avoid floating point arithmetic, consider the value below value m.

m = (y2 – y1)/(x2 – x1)

We multiply both sides by (x2 – x1)

We also change slope_error to slope_error * (x2 – x1). To avoid comparison with 0.5, we further change it to slope_error * (x2 – x1) * 2.

Also, it is generally preferred to compare with 0 than 1.

// Modifying the above algorithm to avoid floating // point arithmetic and use comparison with 0. void bresenham(x1, x2, y1, y2) { m_new = 2 * (y2 - y1) slope_error_new = [Some Initial Value] for (x = x1, y = y1; x = 0)
{
y++;
slope_error_new -= 2 * (x2 - x1);
} } The initial value of slope_error_new is 2*(y2 – y1) – (x2 – x1). Refer this for proof of this value

# Jordan curve theorem

Consider a simple polygon P. We will show that the points of the plane are divided into two sets A and B, having the following property: any two points belonging to the same set can be joined by a polygonal chain which does not cross P; also, any two points belonging to different sets cannot be joined by a polygonal chain such that this chain does not intersect P. Note that the common boundary of A and B is our polygon P. In this case, we will let the set A correspond to the outside set and the set B to the inside set. 

Proof steps: 

Chose a fixed direction in the plane; define the parity of a point.
Prove that if any point p1 of A is joined to any point p2 of B by a polygonal path, then this path must intersect P.
Prove that any two points of the same set (A or B) can be joined by a polygonal path not intersecting P.
The proof begins with chosing a fixed direction in the plane. Let this direction be non-parallel to any of the edges of P. This can always be done since P has a finite number of edges. 
Dealing with intersections 
The sets A and B can now be defined in the following way. Consider a point p and the ray through it, in the fixed direction we chose at the previous step. Then the point p belongs to the set A, if this ray intersects P an even number of times. On the other hand, p belongs to B if the ray intersects our polygon P an odd number of times. 

We define the concept of parity in the following way: two points have the same parity if they belong to the same set, either A or B. 
We now make the following note: all points on a segment not intersecting P, have the same parity. This is obvious: 

chose a fixed direction in the plane
consider a ray in this fixed direction
a point p moving along this ray will have its parity changed only when the ray intersects our polygon at one of its vertices v. But even here, the parity of the point won't actually change, because of the following rule that we make up:  we will count an intersection only when the two edges of P that come together at v, are on different sides of the ray. We will not consider as an intersection the case where the two edges of P meeting at v are on the same side of the ray. 
This implies that if any point p1 of A is joined to any point p2 of B by a polygonal path, then this path must intersect P because otherwise, all the points on this path (and p1 and p2 in particular) would have the same parity. 
 Now we direct our attention to the last step in our proof, where we show that any two points of the same category (A or B) can be joined by a path which doesn't intersect P. 

consider any two points p and q belonging to the same set, A or B.
if the line segment from p to q does not intersect P, we have the desired path and we're done.
else, consider the first intersection of this segment with P. Call this point p'. Also, consider the last intersection of Constructing a path between p and q.the segment with P and call that point q'. We now construct a path starting at p and along the segment pq. Before we reach p', our path separates from pq and from the boundary of P but continues along this boundary until it reaches the continuation of pq. Finally, it comes back to q'. Does this path actually intersect pq between q' and q? If we can show that this is the case, then we have the desired path from p to q, which does not intersect P. This path will be obtained by continuing the original path along q'q until q is reached. Let's stop for a moment and note that any two points r and s close enough, but on opposite sides of an edge of P, always have different parity. This is true since the ray from one point (say r) will intersect P in one more point than the ray from the other point (say q). Back to our case, the parity changes as our path crosses pq between q' and q, since p, q and all other points on this path have the same parity. Therefore we have an intersection point between q' and q, so we can obtain a path between p and q, which does not intersect P. Since p and q belong to the same set (from our original supposition), the theorem for the case of polygons is now proved.
