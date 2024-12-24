# MAGE Core Tenets

## 1. Simple Component-First Approach
- Components are the building blocks
- Each component has a clear, single responsibility
- Components should be easy to add and remove
- Blueprint-friendly component setup
- Minimal boilerplate for new components

## 2. Clear System Organization
- Systems process related components
- One system = one feature
- Systems can be enabled/disabled easily
- Clear update order for systems
- Easy to understand dependencies

## 3. Event-Driven Communication
- Use event system for component communication
- Keep components decoupled
- Events should be easy to create and handle
- Support both Blueprint and C++ events
- Clear event flow

## 4. Practical Performance
- Focus on common use cases first
- Optimize only when needed
- Keep memory layout simple
- Use standard Unreal patterns
- Profile before complex optimization

## 5. User-Friendly Workflow
- Easy setup in Blueprint
- Clear debugging visualization
- Straightforward component configuration
- Intuitive system management
- Quick iteration cycle

## 6. Maintainable Features
- Features are self-contained
- Easy to add new features
- Simple to modify existing features
- Clear feature dependencies
- Feature toggle support

## Do's
1. Keep components focused and simple
2. Use clear naming conventions
3. Follow UE component patterns
4. Make features self-contained
5. Document public interfaces
6. Provide Blueprint access
7. Use existing UE systems
8. Keep dependencies clear
9. Add debug visualization
10. Write example usage

## Don'ts
1. Over-engineer solutions
2. Add premature optimization
3. Create deep inheritance chains
4. Make complex component dependencies
5. Break UE conventions
6. Hide important settings
7. Mix feature responsibilities
8. Create tight coupling
9. Skip documentation
10. Force specific patterns

## Implementation Guidelines

### Components
- Clear purpose
- Minimal dependencies
- Easy to understand properties
- Standard UE lifecycles
- Blueprint exposed where needed

### Systems
- Process specific component types
- Clear update ordering
- Simple enable/disable
- Easy to debug
- Focused responsibility

### Events
- Clear naming
- Simple payload
- Easy to bind
- Support both runtime and editor
- Blueprint friendly

### Features
- Self-contained
- Toggle support
- Clear dependencies
- Easy configuration
- Example usage

## Success Metrics
1. How quickly can someone add a new component?
2. How easily can systems be modified?
3. How clear is the event flow?
4. How fast is the iteration cycle?
5. How discoverable are features?

## Development Priorities
1. User workflow
2. Clear documentation
3. Example implementations
4. Debug support
5. Feature completeness

## Key Principles
1. Make the simple case easy
2. Keep the complex case possible
3. Follow UE patterns
4. Clear over clever
5. Practical over perfect

Remember: Focus on making the common tasks easy and straightforward. Complex optimizations can come later when needed.