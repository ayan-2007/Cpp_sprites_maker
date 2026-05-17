# Cpp_sprites_maker

A C++ terminal-based sprite renderer that recreates retro game characters using 2D arrays and ANSI escape codes.

The struggle of not having enough sprites and manually editing every single pixel of an enemy sprite in an OOP project got me thinking.

I have modern AI tools. Developers in the 90s and 2000s didn't.

So how did they actually make those iconic game sprites back then?

After some digging, I found the answer: it was all hand-crafted pixel arrays. Every character, every enemy, every animation frame designed cell-by-cell, often with nothing but a grid and a color palette.

That sent me down a rabbit hole.

I started experimenting with 2D arrays and ANSI escape codes in C++—the same fundamental concepts those developers used—to render colored pixel blocks directly in the terminal, with AI assistance.

The result: Sonic the Hedgehog rendered in a command prompt.

Not perfect. But watching a recognizable character appear on screen from nothing but an integer array and a few `cout` statements hit differently than I expected.

Those developers had no AI assistants, no high-res reference tools, no instant iteration. Just patience, a real understanding of their constraints, and an eye for which pixels actually mattered.

Modern tools give us speed. But the fundamentals those pioneers worked within are still worth understanding.

Sometimes the best way to appreciate how far we have come is to try doing it the old way.
