# MAGE Framework
## Modular Actor Gameplay Extension System

MAGE is an experimental learning project that explores implementing Entity Component System (ECS) patterns and Gameplay Ability System (GAS) concepts in Unreal Engine. It serves as an educational resource for understanding how to bridge different architectural approaches in game development.

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.1+-blue.svg)](https://www.unrealengine.com)

## ⚠️ Educational Project Notice

This is a **learning project** designed to explore and understand:
- ECS architecture principles in an Unreal context
- Alternative approaches to Unreal's Gameplay Ability System
- High-performance entity management
- Data-oriented design patterns

While functional, this framework is primarily for educational purposes and may not be suitable for production use without significant testing and refinement.

## 🎯 Project Goals

1. **Learning & Exploration**
   - Understand ECS principles
   - Study GAS architecture
   - Explore performance optimization
   - Practice systems design

2. **Architectural Experimentation**
   - Bridge ECS and Unreal's actor model
   - Implement GAS concepts without actor dependencies
   - Explore data-oriented design
   - Test different optimization strategies

3. **Documentation & Teaching**
   - Clear code examples
   - Detailed explanations
   - Implementation alternatives
   - Design decision rationales

## 🏗️ Core Features

- **ECS-Style Architecture**
  - Entity pooling for performance
  - Component-based design
  - System-driven logic
  - Data-oriented approach

- **Gameplay Tags Integration**
  - Tag-based filtering
  - Component categorization
  - System matching
  - Dynamic queries

- **Ability System Concepts**
  - Ability definitions
  - Effect management
  - Visual feedback
  - State handling

- **Performance Focus**
  - Efficient entity storage
  - Component pooling
  - Optimized queries
  - Minimal overhead

## 🔍 Key Design Decisions

1. **Entity Management**
   ```cpp
   // Entities are just IDs, all data lives in components
   struct FMAGEEntityId
   {
       uint32 Index;
       uint32 Version;
   };
   ```

2. **Component Storage**
   ```cpp
   // Components are pure data
   struct FHealthComponentData : public FMAGEComponentData
   {
       float CurrentHealth;
       float MaxHealth;
   };
   ```

3. **System Architecture**
   ```cpp
   // Systems process component data
   class UHealthSystem : public UMAGESystemBase
   {
       virtual void Update(float DeltaTime) override;
   };
   ```

## 📚 Learning Resources

This project draws inspiration from and builds upon these concepts:

- [Entity Component System Overview](https://en.wikipedia.org/wiki/Entity_component_system)
- [Unreal Engine Gameplay Ability System](https://docs.unrealengine.com/5.1/en-US/gameplay-ability-system-for-unreal-engine/)
- [Data-Oriented Design](https://en.wikipedia.org/wiki/Data-oriented_design)
- [Gameplay Tags in Unreal Engine](https://docs.unrealengine.com/5.1/en-US/gameplay-tags-in-unreal-engine/)

## 🚀 Getting Started

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/mage-framework.git
   ```

2. **Add to Your Project**
   ```
   Copy the MAGE plugin to your project's Plugins directory
   Enable the plugin in your .uproject file
   ```

3. **Basic Usage**
   ```cpp
   // Create an entity
   FMAGEEntityId Entity = EntityManager->CreateEntity();
   
   // Add components
   auto& Health = EntityManager->AddComponent<FHealthComponentData>(Entity);
   Health.MaxHealth = 100.0f;
   
   // Systems automatically process matching components
   ```

## ⚙️ Core Systems

1. **Entity Management**
   - Entity creation/destruction
   - Component attachment
   - Entity pooling
   - Memory management

2. **Component System**
   - Data storage
   - Tag integration
   - State management
   - Efficient access

3. **Ability Framework**
   - Ability definitions
   - Effect system
   - Visual feedback
   - State handling

## 📋 Example Usage

```cpp
// Define a component
USTRUCT()
struct FHealthComponent : public FMAGEComponentData
{
    GENERATED_BODY()
    
    float CurrentHealth = 100.0f;
    float MaxHealth = 100.0f;
};

// Create a system
UCLASS()
class UHealthSystem : public UMAGESystemBase
{
    GENERATED_BODY()
    
    virtual void Update(float DeltaTime) override
    {
        // Process all entities with health components
        auto View = GetEntityManager()->CreateView<FHealthComponent>();
        for (auto [Health] : View)
        {
            // Update health logic
        }
    }
};
```

## 🔧 Limitations & Considerations

- **Experimental Nature**: This is a learning project, not production-ready code
- **Performance Testing**: Needs thorough benchmarking
- **Networking**: Basic implementation, needs more work
- **Documentation**: Work in progress
- **Testing**: Needs more comprehensive tests

## 🤝 Contributing

This is an educational project, and we welcome contributions that help others learn:
- Code examples
- Documentation improvements
- Performance optimizations
- Tutorial content
- Bug fixes

## 📖 Learning Goals

1. **Understanding ECS**
   - Component data separation
   - System-driven logic
   - Entity management
   - Performance optimization

2. **GAS Concepts**
   - Ability implementation
   - Effect systems
   - State management
   - Visual feedback

3. **Performance Patterns**
   - Data orientation
   - Memory management
   - Efficient iteration
   - Cache optimization

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
