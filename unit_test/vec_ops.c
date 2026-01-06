#include "vector.h"

// Helper function to print vectors
static
void print_vector(const char *name, t_vec3 v)
{
    printf("%s: (%.3f, %.3f, %.3f, w=%.3f)\n", name, v.x, v.y, v.z, v.w);
}

// Helper function to check if two vectors are equal within epsilon
static
bool vectors_equal(t_vec3 a, t_vec3 b, double epsilon)
{
    return (fabs(a.x - b.x) < epsilon && 
            fabs(a.y - b.y) < epsilon && 
            fabs(a.z - b.z) < epsilon && 
            fabs(a.w - b.w) < epsilon);
}

// Helper function to check if two doubles are equal within epsilon
static
bool doubles_equal(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

int	main(void)
{
    const double EPSILON = 1e-10;
    printf("=== Vector Library Test Suite for Ray Tracing Engine ===\n\n");

    // Test 1: Constructor functions
    printf("1. Testing Constructor Functions:\n");
    t_vec3 point = point_constructor(1.0, 2.0, 3.0);
    t_vec3 vector = vector_constructor(4.0, 5.0, 6.0);
    
    print_vector("Point", point);
    print_vector("Vector", vector);
    
    if (point.w == 1.0 && vector.w == 0.0)
        printf("✓ Constructor tests passed\n\n");
    else
        printf("✗ Constructor tests failed\n\n");

    // Test 2: Length functions
    printf("2. Testing Length Functions:\n");
    t_vec3 unit_x = vector_constructor(1.0, 0.0, 0.0);
    t_vec3 test_vec = vector_constructor(3.0, 4.0, 0.0);
    
    print_vector("Unit X vector", unit_x);
    print_vector("Test vector (3,4,0)", test_vec);
    
    double len_sq = vector_length_squared(test_vec);
    double len = vector_length(test_vec);
    
    printf("Length squared: %.3f (expected: 25.0)\n", len_sq);
    printf("Length: %.3f (expected: 5.0)\n", len);
    
    if (doubles_equal(len_sq, 25.0, EPSILON) && doubles_equal(len, 5.0, EPSILON))
        printf("✓ Length tests passed\n\n");
    else
        printf("✗ Length tests failed\n\n");

    // Test 3: Normalization
    printf("3. Testing Normalization:\n");
    t_vec3 vec_to_normalize = vector_constructor(6.0, 8.0, 0.0);
    t_vec3 normalized = vector_normalization(vec_to_normalize);
    
    print_vector("Original vector", vec_to_normalize);
    print_vector("Normalized vector", normalized);
    
    double normalized_len = vector_length(normalized);
    printf("Length of normalized vector: %.6f (should be 1.0)\n", normalized_len);
    
    if (doubles_equal(normalized_len, 1.0, EPSILON))
        printf("✓ Normalization test passed\n\n");
    else
        printf("✗ Normalization test failed\n\n");

    // Test 4: Dot Product
    printf("4. Testing Dot Product:\n");
    t_vec3 a = vector_constructor(1.0, 2.0, 3.0);
    t_vec3 b = vector_constructor(4.0, 5.0, 6.0);
    t_vec3 c = vector_constructor(1.0, 0.0, 0.0); // Unit x
    t_vec3 d = vector_constructor(0.0, 1.0, 0.0); // Unit y
    
    print_vector("Vector A", a);
    print_vector("Vector B", b);
    print_vector("Unit X", c);
    print_vector("Unit Y", d);
    
    double dot_ab = vector_dot_product(a, b);
    double dot_xy = vector_dot_product(c, d);
    
    printf("Dot product A·B: %.3f (expected: 32.0)\n", dot_ab);
    printf("Dot product X·Y: %.3f (expected: 0.0)\n", dot_xy);
    
    if (doubles_equal(dot_ab, 32.0, EPSILON) && doubles_equal(dot_xy, 0.0, EPSILON))
        printf("✓ Dot product tests passed\n\n");
    else
        printf("✗ Dot product tests failed\n\n");

    // Test 5: Cross Product
    printf("5. Testing Cross Product:\n");
    t_vec3 i = vector_constructor(1.0, 0.0, 0.0); // Unit x
    t_vec3 j = vector_constructor(0.0, 1.0, 0.0); // Unit y
    t_vec3 k = vector_constructor(0.0, 0.0, 1.0); // Unit z
    
    print_vector("Unit X (i)", i);
    print_vector("Unit Y (j)", j);
    print_vector("Unit Z (k)", k);
    
    t_vec3 cross_ij = vector_cross_product(i, j);
    t_vec3 cross_jk = vector_cross_product(j, k);
    t_vec3 cross_ki = vector_cross_product(k, i);
    
    print_vector("i × j", cross_ij);
    print_vector("j × k", cross_jk);
    print_vector("k × i", cross_ki);
    
    bool cross_correct = vectors_equal(cross_ij, k, EPSILON) && 
                        vectors_equal(cross_jk, i, EPSILON) && 
                        vectors_equal(cross_ki, j, EPSILON);
    
    if (cross_correct)
        printf("✓ Cross product tests passed\n\n");
    else
        printf("✗ Cross product tests failed\n\n");

    // Test 6: Vector Addition
    printf("6. Testing Vector Addition:\n");
    t_vec3 add_a = vector_constructor(1.0, 2.0, 3.0);
    t_vec3 add_b = vector_constructor(4.0, 5.0, 6.0);
    t_vec3 add_result = vector_add(add_a, add_b);
    
    print_vector("Addend A", add_a);
    print_vector("Addend B", add_b);
    print_vector("A + B", add_result);
    
    t_vec3 expected_add = vector_constructor(5.0, 7.0, 9.0);
    if (vectors_equal(add_result, expected_add, EPSILON))
        printf("✓ Addition test passed\n\n");
    else
        printf("✗ Addition test failed\n\n");

    // Test 7: Vector Subtraction
    printf("7. Testing Vector Subtraction:\n");
    t_vec3 sub_a = vector_constructor(5.0, 7.0, 9.0);
    t_vec3 sub_b = vector_constructor(1.0, 2.0, 3.0);
    t_vec3 sub_result = vector_sub(sub_a, sub_b);
    
    print_vector("Minuend A", sub_a);
    print_vector("Subtrahend B", sub_b);
    print_vector("A - B", sub_result);
    
    t_vec3 expected_sub = vector_constructor(4.0, 5.0, 6.0);
    if (vectors_equal(sub_result, expected_sub, EPSILON))
        printf("✓ Subtraction test passed\n\n");
    else
        printf("✗ Subtraction test failed\n\n");

    // Test 8: Vector Scaling
    printf("8. Testing Vector Scaling:\n");
    t_vec3 scale_vec = vector_constructor(2.0, 3.0, 4.0);
    t_vec3 scaled = vector_scale(scale_vec, 2.5);
    
    print_vector("Original vector", scale_vec);
    print_vector("Scaled by 2.5", scaled);
    
    t_vec3 expected_scaled = vector_constructor(5.0, 7.5, 10.0);
    if (vectors_equal(scaled, expected_scaled, EPSILON))
        printf("✓ Scaling test passed\n\n");
    else
        printf("✗ Scaling test failed\n\n");

    // Test 9: Array access (union functionality)
    printf("9. Testing Array Access:\n");
    t_vec3 array_test = vector_constructor(10.0, 20.0, 30.0);
    printf("Vector via named fields: (%.1f, %.1f, %.1f)\n", array_test.x, array_test.y, array_test.z);
    printf("Vector via array access: (%.1f, %.1f, %.1f)\n", array_test.v[0], array_test.v[1], array_test.v[2]);
    
    bool array_access_works = (array_test.x == array_test.v[0]) && 
                             (array_test.y == array_test.v[1]) && 
                             (array_test.z == array_test.v[2]);
    
    if (array_access_works)
        printf("✓ Array access test passed\n\n");
    else
        printf("✗ Array access test failed\n\n");

    // Test 10: Edge cases
    printf("10. Testing Edge Cases:\n");
    t_vec3 zero_vec = vector_constructor(0.0, 0.0, 0.0);
    t_vec3 zero_normalized = vector_normalization(zero_vec);
    
    print_vector("Zero vector", zero_vec);
    print_vector("Normalized zero vector", zero_normalized);
    
    bool zero_test = (zero_normalized.x == 0.0 && zero_normalized.y == 0.0 && 
                      zero_normalized.z == 0.0 && zero_normalized.w == 0.0);
    
    if (zero_test)
        printf("✓ Edge case tests passed\n\n");
    else
        printf("✗ Edge case tests failed\n\n");

    printf("=== Test Suite Complete ===\n");
    
    return (0);
}
