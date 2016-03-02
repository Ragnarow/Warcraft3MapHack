/* 
	DLL on Windows need relocations, (opposite to Linux which
	use Position Independant Code), so after mmap our DLL in
	the game address space, we will need to patch every relocations
*/
void patch_reloc(void);

/* 
	After our DLL is mmap in game memory space, and relocated, we
	will probably use dependencies that are outside of our address space.
	We need to LoadLibrary() them, and patch the IAT manually
*/
void patch_IAT(void);