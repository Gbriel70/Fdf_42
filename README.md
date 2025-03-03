# Fdf_42

<div align="center"><h1>FDF [125 / 100]</h1></div>

<div align="center">
  <a href="https://github.com/Gbriel70/Fdf" target="_blank"><img height=300 src="https://github.com/byaliego/42-project-badges/raw/main/badges/fdfm.png"></a>
</div>

<br><br>

# About the Project

FDF is a project by Escola 42 that aims to create a three-dimensional representation of a 2D map using isometric projection. The program receives a map file containing elevation information and generates a 3D visual representation. To do this, we use MLX (MiniLibX), a low-level graphics library provided by 42.

<img src="https://github.com/Gbriel70/Fdf_42/blob/main/img/42.png" />

[**What is isometric projection ?](https://pikuma.com/blog/isometric-projection-in-games)

# Rendering Algorithm

In the mandatory part of the project, we used the Bresenham algorithm to draw the lines that connect the points of the grid. This algorithm is efficient for rasterizing straight line segments in a discrete space, ensuring an accurate visualization of the map structures.

## How the Bresenham Algorithm Works

The Bresenham algorithm is an incremental method that allows you to draw a line between two points without the need for decimal calculations. It works by evaluating the slope of the line and deciding which adjacent pixel should be activated to keep the line as close as possible to the mathematically ideal path.

The basic logic of the algorithm can be summarized as:

Determine the difference between the X and Y coordinates of the end points of the line.

Calculate a cumulative error to decide when to increment Y as we move along X (or vice versa).

Update the cumulative error at each step to ensure that the line is drawn as accurately as possible.

[**algorithm explained in more detail in this article](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

# How to run the project


#### 1. clone
```bash
    git clone https://github.com/Gbriel70/Fdf_42.git
```
#### 2. Run set.sh to push libs
```bash
    bash ./set.sh
```
### 3. execute make
```bash
    make 
```

### 4. run map
```bash
    ./fdf ./maps/test_maps/42.fdf
```

# Bonus Part

In the bonus part of the project, we added interactivity to the FDF, allowing the user to manipulate the map view in real time.

## Implemented Features:

#### Zoom: Increase and decrease the size of the projection to better visualize the details.

#### Rotation: Rotate the map on different axes to change the perspective.

#### Translation: Move the map on the screen to adjust it to the center of the view.

#### Projection Change: Switch between isometric and parallel projection for different representations.

## Implementation

#### Zoom was implemented by adjusting the scale of the points when drawing the lines.

#### Rotation was based on 3D rotation matrices applied to the coordinates of the points.

#### Translation was applied by adding fixed values ​​to the X and Y coordinates.

#### Changing the projection allows the map to be viewed in different ways, improving the user experience.

# How to run


#### 1. clone
```bash
    git clone https://github.com/Gbriel70/Fdf_42.git
```
### 2. execute make
```bash
    make bonus
```
### 3. run map
```bash
    ./fdf_bonus ./maps/test_maps2/van_gogh.fdf
```

<img src="https://github.com/Gbriel70/Fdf_42/blob/main/img/van.png" />

# Algorithm

In the bonus part of the project, I implemented the Xaolim Wou algorithm to improve the rendering process of lines between points of the 3D mesh. This algorithm is a variation of the Digital Differential Analyzer (DDA) method, which is used to draw lines efficiently and accurately.

The Xaolim Wou algorithm works through an incremental approach. Instead of calculating all the points of a line at once, the algorithm determines the position of the intermediate points based on an increment on both the X and Y axes, continuously adjusting the line until it reaches the final point. This results in a more fluid rendering, especially when dealing with large meshes, as in the case of the FDF project, where the precision in the connection between the points is crucial for the proper visualization of the 3D structure.

Using this algorithm not only optimizes graphics performance, but also ensures consistency in the display of lines, providing an accurate representation of the 3D mesh on the 2D screen.

[**algorithm Xaolim Wou in more details](https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm)


<img src="https://github.com/Gbriel70/Fdf_42/blob/main/img/ney.png" />
