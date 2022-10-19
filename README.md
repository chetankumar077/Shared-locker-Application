# Shared-locker-Application

This is a real life application program that resembles a bank locker system among k users containing two modules, namely CONFIGURE and USE.
In CONFIGURE module, there will be a locker that will be shared among 'k' users. From the given primary key L, we generate k prime numbers and k distinct secondary keys.
Now we store the k prime numbers and the locker id in file and not store the primary key and secondary keys to maintain privacy.

In USE module, provided k secondary keys as input from the user, read the k prime numbers associated with the locker id from the file, from this information
we generate the primary key L using the Chinese Remainder theorem.

Provided k divisors and their respective remainders, we can generate least number as a unique solution that leaves these remainders when divided by these divisors
