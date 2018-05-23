# Class matrix in c++
  A matrix class with operators overloaded, for_each, encapsulation and acess using matrix(i,j) notation. At this moment the class is for a int matrix, but i will post a generic version with more funcionalities.
      
# What does the class have?
  This matrix was designed to facilitate its use and yet have dynamic tools to increase the possibilities of use. The following features are currently available:
  
 Operators: 
 
     +  sum of matrix
  
     += (self) sum of matrix
             
     -  substraction of matrix
             
     -= 
             
     *  either multiply a matrix with another or a matrix with a scalar number 
             
     *= (self)either multiply a matrix with another or a matrix with a scalar number 
             
     ^  power of matrix
             
     ^= (self)power of matrix
             
     == check with 2 matrices are equal
             
     != check with 2 matrices are different
                        
  Methods:
    
    dimension()         return a pair with dimension of the matrix<row,column>
    
    main_diagonal()     return a vector of int with the members of the main diagonal.
    
    rows()              get the count of rows.
    
    columns();          get the count of columns.
    
    rotate_matrix()     return false if isnt a square matrix, else return true and rotate the matrix 90 degrees clockwise.
    
    transpose()         transpose the matrix
    
    is_symmetry()       check if matrix is symmetry return true if so,else false
    
    is_anti_symmetry()  check if matrix is anti-symmetry return true if so, else false
    
    is_identity()       check if the main diagonal members are one and the rest is zero
    
    is_upper_triangle() check if the members upper the main diagonal are zero
    
    is_lower_triangle() check if the members below the main diagonal are zero
# How for_each works ?
