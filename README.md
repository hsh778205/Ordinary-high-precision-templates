# Ordinary-high-precision-templates
High-precision computing for ordinary numbers (non-floating points) for functional perfection, efficiency and compatibility

I thought it was a good code for myself, although I didn't encapsulate it as a class or put it in the header file.

I think it's just a structure, just fine

Here's what to say.

First, the array version is obsolete because it does not support dynamic storage, there will be a lot of space left, a lot of unnecessary computation loss (although that's not a thing for the computer...). )

So I used the vector version.

The structure is named number, which means that it is actually a large number

Features currently supported

The ordinary four operations (although there are negative numbers, but not yet perfect!) ), directly with symbols instead of functions!

Order (.factor))

Power (.power()))

Minimum common multiple (gcd() or .gcd())

Through Friends, you can even use cout and cin directly to input and output!

