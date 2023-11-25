# Iridium Language Reference
## Terminologies
### Value
A value is a piece of data that can be represented by a finite number of bits.
### Type
A type is a possible set of values.
### Operator
An operator is a function that takes one or more values and returns a value or a value tuple. It can have a sub-region optionally.
### Value
A value is the result of an operator or a value passed to an operator/a block.
### Attributes
Attributes describes the metadata of a value (range/distribution/TBAA). It can be attached to an operand and propagated along the use-def chain. Attributes that can be attached are determined by the type of the operand. It is widely used in the flow-sensitive data analysis.
### Metadata
Metadata provides additional information about.
### Block
A block is a DAG of operators. It takes an entry state and some arguments. A block must end with an operator which implements the `Terminator` trait.
### Region
A region is a set of blocks. It also maintains the control flow graph (CFG) and the dominator tree (DT) of these blocks.
### State
A state models all side effects of an operator. It can be passed to an operator as an operand and returned by an operator. It determines the execution order of operators (e.g., a load must be executed after a store). Thus we can easily track them in our data analysis framework.
## Undefined Behavior
### Poison Value
A poison value represents a violation of an assumption. Each operation either propagates `poison` or raise UB.
### Valid Transformation
A transformation is valid when, for each possible input state, the target function displays a subset of the behaviors of the source function. It allows a transformation to remove non-determinism, but not to add it.

## Type System
### Scalars
#### Integers
##### Boolean
A boolean value can be either `true` or `false`. It is often used by conditional branch operators.
Available attributes: `probabilty`, `no_poison`
Avaliable operators: `and`, `or`, `xor`, `logical_and`, `logical_or`
##### Signed Integer
A signed integer represents a integer value in range `[-2^(n-1), 2^(n-1)-1]`, where `n` is the bit width of the integer. The result of a signed integer is a poison value if signed overflow occurs.
Avaliable attributes: `is_power_of_2`, `signed_range`, `distribution`, `defined`
Avaliable operators: `add`, `sub`, `mul`, `div`, `rem`, `bitcast`, `icmp`, `max`, `min`, `abs`, cast operators
##### Unsigned Integer
A unsigned integer represents a integer value in range `[0, 2^n-1]`, where `n` is the bit width of the integer. The result of a unsigned integer is a poison value if unsigned overflow occurs.
Avaliable attributes: `is_power_of_2`, `unsigned_range`, `distribution`, `defined`
Avaliable operators: `add`, `sub`, `mul`, `div`, `rem`, `icmp`, `max`, `min`, cast operators
##### Bit Integer
A bit integer represents a bit vector. It is often used by bitwise operators.
Avaliable attributes: `non_zero`, `is_power_of_2`, `known_bits`, `distribution`, `bit_distribution`, `defined`
Avaliable operators: `and`, `or`, `xor`, `shl`, `lshr`, `ashr`, `bitcast`, `add`, `sub`, `mul`, `ctlz`, `cttz`, `ctpop`, cast operators
##### Shamt
A shamt represents a shift amount in range `[0, n)`, where `n` is the bit width of the shamt. It is used by shift operators.
Avaliable attributes: `distribution`, `shamt_range`, `defined`
Avaliable operators: `shl`, `lshr`, `ashr`, `infcast`
##### Pointer
The pointer type is an alias of the unsigned integer type with the bit width of target pointer size (e.g., `sizeof(void*) * 8` in C).
#### Floating Points
IEEE 754 half, float and double are supported.
bfloat16 is also supported.
Avaliable attributes: `fp_class`, `fp_range`, `defined`
Avaliable operators: `fadd`, `fsub`, `fmul`, `fdiv`, `fcmp`, `fcopysign`, `fpclass`, math functions
### Vectors
A vector represents a sequence of scalar values.
Avaliable attributes: all attributes that implement the `VectorizableAttribute` trait
Avaliable operators: `splat_vector`, `shuffle_vector`, `insert_vector`, `extract_vector`, `vec/vec_pred.<op>` if `op` implement the `VectorizableOperator` trait, `reduce.<op>` if `op` has an identity, and is both commutative and associative.

## Operator Traits
### GroupOperator

| binop        | commutative | associative | identity   | invertibility |
| ------------ | ----------- | ----------- | ---------- | ------------- |
| signed add   | yes         | yes         | 0          | no            |
| signed mul   | yes         | yes         | 1          | no            |
| unsigned add | yes         | yes         | 0          | no            |
| unsigned mul | yes         | yes         | 1          | no            |
| bit add      | yes         | yes         | 0          | yes           |
| bit mul      | yes         | yes         | 1          | no            |
| bit and      | yes         | yes         | -1         | no            |
| bit or       | yes         | yes         | 0          | no            |
| bit xor      | yes         | yes         | 0          | yes           |
| fadd         | yes         | reassoc     | 0.0 (nnan) | nsz & nnan    |
| fmul         | yes         | reassoc     | 1.0 (nnan) | arcp          |

### VectorizableOperator
It indicates that the operator can be vectorized.

## Basic Operators
### Block Terminators
#### br
```
br tgt(%state, %args...)
```

#### cbr
```
cbr %cond, true_tgt(%state, %args...), false_tgt(%state, %args...)
```
#### switch
```
switch %cond, default_tgt(%state, %args...), 
  [case1, tgt1(%state, %args...)],
  [case2, tgt2(%state, %args...)],
  ...
```
`%cond` must be a bit integer. cases must be constant integers. The default target is optional. If it is not specified, the default target is unreachable.
#### unreachable
```
unreachable %state
```

### Logical Operators
#### logical_and
```
%val = logical_and %a, %b
```
If `%a` is `poison`, `%val` is `poison`.
If `%a` is `false`, `%val` is `false`. Otherwise, `%val` is `%b`.
#### logical_or
```
%val = logical_or %a, %b
```
If `%a` is `poison`, `%val` is `poison`.
If `%a` is `true`, `%val` is `true`. Otherwise, `%val` is `%b`.

### Integer Arithmetic Operators
#### int_const
```
%val = int_const s32 0
```
Generates a constant integer value.
#### add
```
%val = add s32 %a, %b
```
#### sub
```
%val = sub s32 %a, %b
```
#### mul
```
%val = mul s32 %a, %b
```
#### div
```
%val = div s32 %a, %b
```
#### rem
```
%val = rem s32 %a, %b
```
#### icmp
```
%val = icmp eq s32 %a, %b
```
#### abs
```
%val = abs s32 a
```
#### max
```
%val = max s32 %a, %b
```
#### min
```
%val = min s32 %a, %b
```

### Bitwise Operators
#### lshr
```
%val = lshr b32 a, shamt32 b
```
#### ashr
```
%val = ashr b32 a, shamt32 b
```
#### shl
```
%val = shl b32 a, shamt32 b
```
#### and
```
%val = and b32 %a, %b
```
#### or
```
%val = or b32 %a, %b
```
#### xor
```
%val = xor b32 %a, %b
```
#### ctlz
```
%val = ctlz b32 a
```
#### cttz
```
%val = cttz b32 a
```
#### ctpop
```
%val = ctpop b32 a
```

### Floating Point Operators
#### fp_const
```
%val = fp_const f32 0.0
```
Generates a constant floating point value.
#### fadd
```
%val = fadd f32 %a, %b
```
#### fsub
```
%val = fsub f32 %a, %b
```
#### fmul
```
%val = fmul f32 %a, %b
```
#### fdiv
```
%val = fdiv f32 %a, %b
```
#### fmul
```
%val = fmul f32 %a, %b
```
#### fcmp
```
%val = fcmp oeq f32 %a, %b
```
#### fcopysign
```
%val = fcopysign f32 %a, %b
```
#### fpclass
```
class = fpclass f32 a
```

#### math functions

### Cast Operators
#### bitcast
```
%tgt = bitcast s32 %src to b32
```
#### sext
```
%tgt = sext s32 %src to s64
```
#### zext
```
%tgt = zext u32 %src to u64
```
#### infcast
```
%tgt = infcast u32 %src to shamt32
```
#### trunc
```
%tgt = trunc s64 %src to s32
```
#### fpcast
```
%tgt = fpcast f32 %src to f64
```
#### tofp
```
%tgt = tofp s32 %src to f32
```
#### fromfp
```
%tgt = fromfp f32 %src to s32
```

### Memory Operators
#### alloc
```
%p = alloc size, align
```
`alloc` allocates a memory region of `size` bytes on the stack and returns the pointer. The pointer is aligned to `align` bytes. `size` and `align` must be positive constants. `align` must be a power of 2.
#### load
```
%val = load s32 ptr %p, %state
```
#### store
```
%state = store s32 %val to ptr %p, %state
```
#### atomicrmw (atomic read-modify-write)
```
%state, %res = atomicrmw.<op>.<ordering> s32 %val at ptr %p, %state
```
#### atomiccas (atomic compare-and-swap)
```
%state, %res, %oldval = atomiccas.<ordering> s32 %cmpval, %newval at ptr %p, %state
```
### Vector Operators
#### shuffle_vector
```
%val = shuffle_vector <b32 x 16> %a, <b32 x 16> %b, <i32 x 32> <0, 1, 2, ..., 31>
```
#### insert_vector
```
%val = insert_vector <b32 x 16> %a, b32 %b, i32 %idx
```
#### extract_vector
```
%val = extract_vector <b32 x 16> %a, i32 %idx
```
#### vec.<op>
```
%val = vec.<op> <b32 x 16> %a, <b32 x 16> %b
```
#### vec_pred.<op>
```
%val = vec_pred.<op> <bool x 16> %pred, <b1 x 16> %a, <b1 x 16> %b
```
#### reduce.<op>
```
%val = reduce.<op> <b32 x 16> %a
```

### Function Operators
#### func
```
%op = func(%state, %args...) -> %rets... {
  ...
}
```
#### call
```
%state_out, %rets... = call %func(%state_in, %args...)
```
#### ret
```
ret %state, %rets...
```

### Loop Operators
#### for
```
%state_out, %outs... = for %i, %j in (%start, %end, %step, <pred>), (%start, %end, %step, <pred>), %state_in {
  ...
}
```
#### yield
```
yield %state, %rets...
```
#### break
```
break %state, %rets...
```

### Miscellaneous
#### select
```
select %cond, i32 %trueval, i32 %falseval
```
#### merge_state
```
state_out = merge_state (state_ins...)
```
#### poison
```
%val = poison as b32
```
Generates a poison value.

## Attribute Traits
## Attributes

## Fast Math Flags
## Atomic Memory Ordering
