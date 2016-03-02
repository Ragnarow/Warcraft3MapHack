/* 
	This function find the offset of the static game variable in .bss,
	thanks to signature checking. Then we won't have to change our hack 
	every game's release to find the offset.
*/
void *get_player_offset(void);