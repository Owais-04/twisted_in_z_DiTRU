# TWISTED IN Z: AN ADVANCED LAYER OVER DITRU

### This is an additional security layer over DITRU that modifies the dihedral group structure to enhance security further.

### We redefine the fundamental relation from x² = 1 to x² = -1, making multiplication non-commutative and improving resistance against certain attacks.

## KEY FEATURES

1. Enhanced security through non-commutative multiplication
2. Quantum-safe cryptographic design
3. Protection against algebraic and structural attacks
4. Efficient key generation, encryption, and decryption
5. Constant-time implementation in C to prevent side-channel attacks

## IMPLEMENTATION DETAILS

- Extends the DITRU cryptosystem with a modified dihedral group structure
- Changes the fundamental property from **x² = 1** to **x² = -1**, making multiplication non-commutative
- Provides stronger resistance against lattice-based and algebraic attacks
- Retains constant-time implementation for improved security
- Optimized for post-quantum cryptographic applications

## USAGE

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/twisted_in_z_DiTRU.git
   cd twisted_in_z_DiTRU
   ```
2. Compile the C implementation using Makefile:
   ```bash
   make
   ```

### Running the Cryptosystem

To generate keys:

```bash
./twisted_in_z_DiTRU generate_keys
```

To encrypt a message:

```bash
./twisted_in_z_DiTRU encrypt "Your message here"
```

To decrypt a message:

```bash
./twisted_in_z_DiTRU decrypt "Encrypted message here"
```

## SECURITY CONSIDERATIONS

- The modified structure with **x² = -1** introduces non-commutativity, preventing specific algebraic attacks
- Maintains post-quantum security properties
- All cryptographic operations are implemented in **constant time** to prevent timing-based side-channel attacks
- Provides a robust alternative to classical dihedral-based encryption schemes

## FUTURE IMPROVEMENTS

- Further refinement of non-commutative structures for enhanced security
- Integration with additional post-quantum cryptographic techniques
- Performance optimizations for real-world deployment

## CONTRIBUTORS

- [Mohammad owais]
- [Furqan mushtaq]

## LICENSE

This project is licensed under the MIT License.

