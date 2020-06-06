#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>
#include <string>
#include "MyVec.hpp"
#include "glut.h"
//#include "../GLUT32/glut.h"
#include"math.h"
#include <algorithm>

#define EPSILON 1e-6
#define INV_SQRT_2PI 0.3989422804

typedef std::tuple<my_vec::my_vec2, my_vec::my_vec2, my_vec::my_vec2> anchor_pts;

double gauss_weight(int dist_, double sigma_);

// Edge struct
struct Edge
{
    // Variables
    std::string _sourceLabel;                       // Label of source node.
    std::string _targetLabel;                       // Label of target node.
    my_vec::my_vec2 _start;                     // Start point.
    my_vec::my_vec2 _end;                       // End point.
    std::vector<my_vec::my_vec2> _subdivs;      // Subdivision points.
    double _width;                                  // Width.
    std::vector<int> _compatibleEdges;              // List of compatible edge indices.

    /**
     * @brief Edge Constructor.
     * Sets end points, arranges direction and adds first subdivision point.
     * @param sourceLabel_ Source node label.
     * @param targetLabel_ Target node label.
     * @param start_       Start coordinates.
     * @param end_         End coordinates.
     * @param width_       Edge width.
     */
    Edge(std::string sourceLabel_, std::string targetLabel_,
         my_vec::my_vec2 &start_, my_vec::my_vec2 &end_,
         double width_);

    /**
     * @brief add_subdivisions Adds subdivision points.
     */
    void add_subdivisions();

    /**
     * @brief arrange_direction Arranges edge direction to standardize order of
     *                          subdivision points.
     */
    void arrange_direction();

    /**
     * @brief update Updates subdivision point positions.
     * @param forces_ Forces acting on the subdivisions.
     * @param S_      Displacement.
     */
    void update(std::vector<my_vec::my_vec2> &forces_, double S_);

    /**
     * @brief smooth Smoothes edge.
     * @param sigma_ Width of kernel.
     */
    void smooth(double sigma_);


    /**
     * @brief add_spring_forces Increments total forces by the spring forces.
     * @param forces_ Total forces.
     * @param K_      Global spring constant.
     */
    void add_spring_forces(std::vector<my_vec::my_vec2> &forces_, double K_);

    /**
     * @brief add_electrostatic_forces Increments total forces by the electrostatic forces.
     * @param forces_  Total forces.
     * @param edge_    Attracting edge.
     * @param epsilon_ Minimum edge distance.
     */
    void add_electrostatic_forces(std::vector<my_vec::my_vec2> &forces_,
                                  Edge edge_, double epsilon_);

    /**
     * @brief add_gravitational_forces Increments total forces by the graviational forces.
     * @param forces_     Total forces.
     * @param center_     Center.
     * @param exponent_   Exponent.
     *
     * Gravitation force acting on a subdivision points is calculated as
     * F_grav = pow( |s - center|, beta )
     * where s and center are the position of the subdivision point and the graviational center,
     * respectively.
     */
    void add_gravitational_forces(std::vector<my_vec::my_vec2> &forces_,
                                  my_vec::my_vec2 &center_,
                                  double exponent_ );

    /**
     * @brief vector Converts edge into a vector.
     * @return Vector pointing from the start to the end of the edge.
     */
    my_vec::my_vec2 vector();

    /**
     * @brief draw Draws the edge.
     * @param alpha_ Opacity of edge.
     */
    void draw(double alpha_, float r, float g, float b);
    /**
     * @brief center Calculates the center of two vectors.
     * @param p1_ First vector.
     * @param p2_ Second vector.
     * @return    Center vector.
     */
	void hb_draw(double alpha_, float r, float g, float b);
	anchor_pts get_three_points();
	my_vec::my_vec2 get_last_point();
	
	static my_vec::my_vec2 center(my_vec::my_vec2 &p1_, my_vec::my_vec2 &p2_);

    /**
     * @brief project Projects a point to a line.
     * @param point_     Point to project.
     * @param lineStart_ First point of line.
     * @param lineEnd_   Second point of line.
     * @return           Projected point.
     */
    static my_vec::my_vec2 project(my_vec::my_vec2 &point_,
                                       my_vec::my_vec2 &lineStart_,
                                       my_vec::my_vec2 &lineEnd_);

    /**
     * @brief angle_compatilibity Calculates angle compatibility of two edges.
     * @param edge1_ First edge.
     * @param edge2_ Second edge.
     * @return       Angle compatibility.
     */
    static double angle_compatilibity(Edge &edge1_, Edge &edge2_);

    /**
     * @brief scale_compatibility Calculates scale compatibility of two edges.
     * @param edge1_ First edge.
     * @param edge2_ Second edge.
     * @return       Scale compatibility.
     */
    static double scale_compatibility(Edge &edge1_, Edge &edge2_);

    /**
     * @brief scale_compatibility Calculates position compatibility of two edges.
     * @param edge1_ First edge.
     * @param edge2_ Second edge.
     * @return       Position compatibility.
     */
    static double position_compatibility(Edge &edge1_, Edge &edge2_);

    /**
     * @brief scale_compatibility Calculates visibility of an edge on the other.
     * @param edge1_ First edge.
     * @param edge2_ Second edge.
     * @return       Visibility.
     */
    static double edge_visibility(Edge &edge1_, Edge &edge2_);

    /**
     * @brief scale_compatibility Calculates visibility compatibility of two edges.
     * @param edge1_ First edge.
     * @param edge2_ Second edge.
     * @return       Visibility compatibility.
     */
    static double visibility_compability(Edge &edge1_, Edge &edge2_);
};

int compare_edges( Edge edge1_, Edge edge2_ );

#endif // EDGE_HPP
