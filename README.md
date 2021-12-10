# 3D Particle Fountain

## Dev environment
- windows 10
- Mac OS Monterey
- VS Code

## Operation Instructions
To the start the program run this within the directory
```
make
```
A window will apear, this is the default state of the program. 
You will notice that particles are initialized with the following:
- Particle lifespan
- Particle spin 
    - NOTE: particle spin has a random rotation angle around which the particle spins with a constant angle. This made animating a random rotation much easier than the way suggested in the assignment.
- Particle floor collision

To interact with the default state, you may
- Toggle friction mode - toggle `F` or `f` key 
- Rotate the scene - arrow keys 
- Start/Stop simulation - space bar
- Reset simulation - `R` or `r` key
- Toggle Lighting - toggle `L` or `l` key
- There are two lights - select one by pressing `0` or `1`, default light is `0`
    - `w` and `s` control the light position along the x axis
    - `a` and `d` control the light position along the z axis  
    - `+` and `-` control the light position along the y axis     

## Additional Features
You may also interact with the program using the additional features we added;
- show particle trail - toggle `T` or `t`
- Particle explosions - toggle `E` or `e`
- toggle particle additional properties - toggle `P` or `p`
    - this will randomly set some particles to have 0-gravity
    - this will set a random "bounciness" property to particles which makes them bounce with more energy
    - this mode is best used with the trail feature
    - the trails also have material properties (you can see them by moving one of the lights below the platform so the lights do not dim them)

## Authors 
- Purv Patel
- Mostafa Mohsen