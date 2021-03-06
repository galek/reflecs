# reflecs
Reflecs is an entity component system implemented in C99. It's design goal is to
pack as much punch as possible into a small library with a minimal API and zero
dependencies. Here are some of its features:

- A multi-threaded job scheduler
- A module system for organizing components and systems in large projects
- An growing list of reusable modules, including an [SDL renderer](https://github.com/SanderMertens/reflecs-systems-sdl2), [2D physics engine](https://github.com/SanderMertens/reflecs-systems-physics) and [web dashboard](https://github.com/SanderMertens/reflecs-systems-admin)
- An API for obtaining runtime statistics on performance and memory usage
- Automatic and manual time management
- Periodic, reactive and on-demand systems

In addition, reflecs has a flexible architecture with many features that let you
write powerful applications with just a few lines of code:

- Prefabs let you create components in memory once, and reuse it across many entities
- Expressive system signatures, with AND, OR, NOT and optional operators
- Use entities as components to create hierarchies, indexes and DAGs
- Create/delete entities and add/remove components while iterating in a system

Check out the [examples](https://github.com/SanderMertens/reflecs/tree/master/examples) and [documentation](https://github.com/SanderMertens/reflecs/blob/master/include/reflecs.h) to learn more!

## Contents
* [Building](#building)
* [Getting started](#getting-started)
* [Modules](#modules)
* [Example](#example)
* [Concepts](#concepts)
  * [entity](#entity)
  * [component](#component)
  * [system](#system)
  * [identifier](#identifier)
  * [family](#family)
  * [feature](#feature)
  * [tag](#tag)
  * [container](#container)
  * [prefab](#prefab)
  * [module](#module)
  

## Building
To build reflecs, you need to install bake which is currently only supported on
Linux and macOS. See the bake README for installation instructions:

https://github.com/SanderMertens/bake/blob/master/README.md

Then to clone, build and install reflecs, do:

```
bake clone SanderMertens/reflecs
```

## Getting started
To create a new reflecs application, first create a new project:

```
bake init app
```

To add reflecs as a dependency to your application, modify the `project.json` so
that it looks like this:

```json
{
    "id":"app",
    "type":"application",
    "value": {
        "use": ["reflecs"]
    }
}
```

You can now use the reflecs API in your source code. If you get compiler errors for 
missing definitions, make sure that your project includes the (generated) file 
`bake_config.h`, as it contains the include statements for your dependencies.

To run the project, do:

```
bake run app
```

## Modules
Reflecs has a growing ecosystem of modules. The following modules are currently
available:

Module      | Description      
------------|------------------
[reflecs.components.transform](https://github.com/SanderMertens/reflecs-components-transform) | Components for positioning, rotating and scaling entities
[reflecs.components.physics](https://github.com/SanderMertens/reflecs-components-physics) | Components for moving entities
[reflecs.components.graphics](https://github.com/SanderMertens/reflecs-components-graphics) | Components for describing a drawing canvas and camera
[reflecs.components.geometry](https://github.com/SanderMertens/reflecs-components-geometry) | Components for describing geometry
[reflecs.components.input](https://github.com/SanderMertens/reflecs-components-input) | Components for describing keyboard and mouse input
[reflecs.components.http](https://github.com/SanderMertens/reflecs-components-http) | Components for describing an HTTP server with endpoints
[reflecs.systems.transform](https://github.com/SanderMertens/reflecs-systems-transform) | Compute transformation matrices from transform components
[reflecs.systems.physics](https://github.com/SanderMertens/reflecs-systems-physics) | Simple 2D physics engine with limited 3D features
[reflecs.systems.civetweb](https://github.com/SanderMertens/reflecs-systems-civetweb) | A civetweb-based implementation of components-http
[reflecs.systems.admin](https://github.com/SanderMertens/reflecs-systems-admin) | A web-based dashboard for monitoring reflecs performance
[reflecs.systems.sdl2](https://github.com/SanderMertens/reflecs-systems-sdl2) | An SDL2-based renderer
[reflecs.math](https://github.com/SanderMertens/reflecs-math) | Matrix and vector math functions
[reflecs.util](https://github.com/SanderMertens/reflecs-util) | Utility functions and datastructures

## Example
The following code shows a simple reflecs application:

```c
typedef struct Position {
    float x;
    float y;
} Position;

typedef int32_t Speed;

void Move(EcsRows *rows) {
    for (void *row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        Position *p = ecs_data(rows, row, 0);
        Speed *s = ecs_data(rows, row, 1);
        p->x += *s * rows->delta_time;
        p->y += *s * rows->delta_time;
    }
}

int main(int argc, char *argv[]) {
    EcsWorld *world = ecs_init();

    /* Register components and systems */
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Speed);
    ECS_FAMILY(world, Movable, Position, Speed);
    ECS_SYSTEM(world, Move, EcsOnFrame, Position, Speed);

    /* Create entity with Movable family */
    ecs_new(world, Movable_h);

    /* Limit application to 100 FPS */
    ecs_set_target_fps(world, 100);

    /* Progress world in main loop (invokes Move system) */
    while (ecs_progress(world, 0));

    return ecs_fini(world);
}
```

## Concepts
This section describes the high-level concepts used in reflecs, and how they are represented in the API. Rather than providing an exhaustive overview of the API behavior, this section is intended as an introduction to the different API features of reflecs.

### World
A world is a container in which entities, components and systems can be stored and evaluated. An application can create any number of worlds. Data between worlds is not shared. If the application wants to share data between worlds, this has to be done manually. A world in ECS can be created with the `ecs_init` function:

```c
EcsWorld *world = ecs_init();
```

### Entity
An entity is an integer that uniquely identifies an "object" in a system. An entity may have `0..n` components, and each component can be added only once. Entities can be created in reflecs with the `ecs_new` function:

```c
EcsEntity e = ecs_new(world, 0);
```

### Component
Components are datatypes that can be added to an entity. Any C datatype can be registered as a component within reflecs. To register a component, you can use the `ECS_COMPONENT` macro, which wraps around the `ecs_new_component` function:

```c
typedef struct Point {
   int x;
   int y;
} Point;

ECS_COMPONENT(world, Point);
```

The macro will define a `Point_h` variable, which can be used to add the component to an entity with the `ecs_add` function:

```c
ecs_add(world, e, Point_h);
```

Additionally, the component can be added and initialized with the `ecs_set` function:

```c
ecs_set(world, e, Point, {.x = 10, .y = 20});
```

Reflecs components are stored internally as entities, which is why handles to components are of the `EcsEntity` type.

### System
A system is logic (a function) that is executed for every entity that has a set of components that match a system's interest. In reflecs, systems specify their interest, and when they should run. To define a system, you can use the `ECS_SYSTEM` macro, which wraps around the `ecs_new_system` function:

```c
ECS_SYSTEM(world, LogPoints, EcsOnFrame, Point);
```

In this statement, `LogPoints` refers to a C function that will be associated with the system. `EcsOnFrame` identifies the stage in which the system is executed. The `{Point}` identifies the component interest expression. After the macro, an application can use the `LogPoints_h` variable to refer to the system. The system is implemented as a regular C function, like this:

```c
void LogPoints(EcsRows *rows) {
    for (void *row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        Point *p = ecs_data(rows, row, 0);
        printf("Log point (%d, %d)\n", p->x, p->y);
    }
}
```

Systems can be enabled / disabled. By default a system is enabled. To enable or disable a system, you can use the `ecs_enable` function:

```c
ecs_enable(world, LogPoints_h, false);
```

Reflecs systems are stored as entities internally, which is why handles to systems are of the `EcsEntity` type.

### Identifier
Entities in reflecs may have an optional string-based identifier. An identifier can be added to an entity by setting the `EcsId` component, like this:

```c
ecs_set(world, e, EcsId, {"MyEntity"});
```

After a string identifier is added, the entity can be looked up like this:

```c
EcsEntity e = ecs_lookup(world, "MyEntity");
```

Components, systems, tasks, families and prefabs automatically register the `EcsId` component when they are created, and can thus be looked up with `ecs_lookup`.

### Task
A task is a system that has no interest expression. Tasks are run once every frame. Tasks are defined the same way as normal systems, but instead of an interest expression, you specify `0`:

```c
ECS_SYSTEM(world, MyTask, EcsOnFrame, 0);
```

### Family
A family is a group of `1..n` entities. Since components and systems are stored as entities by reflecs, families can also be used to group components and systems. Typical uses for familes are:

- Group components so that they can be added to an entity with a single `ecs_add` call
- Group systems so that they can be enabled or disabled with a single `ecs_enable` call

To define a family, you can use the `ECS_FAMILY` macro, which wraps the `ecs_new_family` function:

```c
ECS_FAMILY(world, Circle, EcsCircle, EcsPosition2D);
```

This defines a family called `Circle` that contains `EcsCircle` and `EcsPosition2D`. The macro will define the `Circle_h` variable, which the application can use to refer to the family:

```c
ecs_add(world, e, Circle_h);
```

Reflecs families are stored as entities internally, which is why handles to families are of the `EcsEntity` type.

### Feature
A feature is a family that contains solely out of systems. To create features, use the `ECS_FAMILY` macro or `ecs_new_family` function.

### Tag
A tag is a component that does not contain any data. Internally it is represented as a component with data-size 0. Tags can be useful for subdividing entities into categories, without adding any data. A tag can be defined with the `ECS_TAG` macro:

```c
ECS_TAG(world, MyTag);
```
The macro will define the `MyTag_h` variable, which an application can then use as a regular component, like with the ecs_add function:

```c
ecs_add(world, e, MyTag_h);
```

Tags, like components, are stored as entities internally which is why handles to tags are of the `EcsEntity` type.

### Container
A container is an entity that can contain other entities. Since components are stored as entities in reflecs, and components can be added with the `ecs_add` function, it is similarly possible to add entities to entities with the `ecs_add` function. The only restriction is that the entity that is to be added must be a "container". To turn an entity in a container, add the builtin `EcsContainer` component, like so:

```c
// equivalent to calling ecs_new(world, 0) + ecs_add(world, my_container, EcsContainer_h)
EcsEntity my_container = ecs_new(world, EcsContainer_h);
```

This entity can now be used like a component:

```c
ecs_new(world, e, my_container);
```

The above code constructs a hierarchy with a parent ("my_container") and a child ("e"). For an example of how to walk over this hierarchy, see the `dag` example in the examples directory.

### Prefab
Prefabs are a special kind of entity that enable applications to reuse components values across entities. To create a prefab, you can use the `ECS_PREFAB` macro, or `ecs_new_prefab` function:

```c
ECS_PREFAB(world, CirclePrefab, EcsCircle, EcsPosition2D);
```

This defines a prefab with the `EcsCircle` and `EcsPosition2D` components. The macro will declare a `Circle_h` variable, which can be used by the application to refer to the prefab. We can now add this prefab to regular entities:

```c
EcsEntity e1 = ecs_new(world, CirclePrefab_h);
EcsEntity e2 = ecs_new(world, CirclePrefab_h);
```

This will make the `EcsCircle` and `EcsPosition2D` components available on entities `e1` and `e2`, similar to a family. In contrast to familes, component values of `EcsCircle` and `EcsPosition2D` are now shared between entities, and stored only once in memory. Since a prefab can be used as a regular entity, we can change the value of a prefab component with the `ecs_set` function:

```c
ecs_set(world, CirclePrefab_h, EcsCircle, {.radius = 10});
```

This will change the value of `EcsCircle` across all entities that have the prefab. Entities can override component values from a prefab, by either adding or setting a component on themselves, using `ecs_add` or `ecs_set`. When a component is added using `ecs_add`, it will be initialized with the component value of the prefab.

### Module
Modules are used to group entities / components / systems. They can be imported with the `ECS_IMPORT` macro:

```c
ECS_IMPORT(world, EcsComponentsTransform, 0);
```

This will invoke the `EcsComponentsTransform` function, which will define the entities / components / systems. Furthermore, the macro will declare the variables to the entity / component / system handles to the local scope, so that they can be accessed by the code. 

In large code bases modules can be used to organize code and limit exposure of internal systems to other parts of the code. Modules may be implemented in separate shared libraries, or within the same project. The only requirements for using the `ECS_IMPORT` macro is that the name of the module (`EcsComponentsTransform`) can be resolved as a C function with the right type. For an example on how to implement modules, see the implementation of one of the reflecs modules (see above).

Modules can be imported multiple times without causing side effects.
