/*

@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "character.h"

void array_dump(CharacterList array) {
  for (int alignment=0; alignment<CHARACTER_ALIGNMENTS; ++alignment) {
    for (int charttype=0; charttype < CHARACTER_TYPES; ++charttype) {
      Character character = array[charttype][alignment];

      char *str_alignment = (character.alignment == good) ? "Good" : "Evil";
      char *str_alive = (character.alive) ? "Yes" : "Nope";

      fprintf(stdout, "Character '%s': Life=%u/100, Strength=%u/10, Agility=%u/10, alignment='%s', Alive='%s'\n",
                        NAMES[character.name], character.life, character.strength,
                        character.agility, str_alignment, str_alive);
    
    }
  }
}

float array_alive_mean_life(CharacterList array) {
    /* COMPLETARDO */
    unsigned int total_life = 0;
    unsigned int alive_count = 0;

    for (int alignment = 0; alignment < CHARACTER_ALIGNMENTS; ++alignment) {
        for (int charttype = 0; charttype < CHARACTER_TYPES; ++charttype) {
            Character character = array[charttype][alignment];
            if (character.alive) {
                total_life += character.life;
                alive_count++;
            }
        }
    }

    if (alive_count == 0) {
        return 0.0;
    }

    return (float)total_life / alive_count;
}

unsigned int array_from_file(CharacterList array, const char *filepath) {
  FILE *file = NULL;

  // check if file exists
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  // read the file
  unsigned int readed = 0;
  while (!feof(file) && readed < 8) {
    charttype_t charttype;
    alignment_t alignment;

    char s_charttype, s_alignment;
    int res=fscanf(file, " [%c %c] ", &s_charttype, &s_alignment);
    if (res != 2) {
        fprintf(stderr, "Error reading type and alignment.\n");
        exit(EXIT_FAILURE);
    }
     switch (s_charttype) {
            case 'a': charttype = agile; break;
            case 'p': charttype = physical; break;
            case 't': charttype = tank; break;
            case 'm': charttype = magic; break;
            default: 
                fprintf(stderr, "Unknown character type.\n");
                exit(EXIT_FAILURE);
        }

        switch (s_alignment) {
            case 'g': alignment = good; break;
            case 'e': alignment = evil; break;
            default: 
                fprintf(stderr, "Unknown alignment.\n");
                exit(EXIT_FAILURE);
        }

    /* convertir la letra de `s_charttype` en un valor `charttype_t` y asignarlo
     * a la variable  `charttype`:
     *
     * 'a' --> agile
     * 'p' --> physical
     * 't' --> tank
     * 'm' --> mage
     *
     */

    /* convertir la letra de `s_alignment` en un valor `aligment_t` y asignarlo
     * a la variable  `alignment`:
     *
     * 'g' --> good
     * 'e' --> evil
     *
     */

    // Reads the name and obtains an name_t value
    name_t name = read_character_name(file);

    Character character = character_from_file_line(file, name, alignment);
        array[charttype][alignment] = character;/*completar cargando el contenido del archivo*/;

    /* COMPLETAR: Almacenar en la tabla*/
    ++readed;
  }
  /* COMPLETAR SI ES NECESARIO CON ALGUNA VERIFICACIÓN FINAL */

  // close the file
  fclose(file);

  return readed;
}
