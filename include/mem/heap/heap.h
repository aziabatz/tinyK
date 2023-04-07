#ifndef HEAP_H
#define HEAP_H

#include <types.h>
#include <stdbool.h>
#include <mem/types.h>
#include <stddef.h>
#include <mem/virt/paging.h>

#define HEAP_BLOCK_MARK 0xEAEAFAF0

/**
 * @brief Una estructura que representa un bloque de memoria en el heap.
 */
struct block_descriptor
{
    uint32 mark;                  /**< Un marcador para fines de depuración. */
    bool used;                      /**< Si el bloque está en uso o libre. */
    virt_t base;                    /**< La dirección virtual del comienzo del bloque. */
    size_t length;                  /**< La longitud del bloque. */
    struct block_descriptor * next;  /**< Puntero al siguiente bloque en el heap. */
    struct block_descriptor * prev;
};

typedef struct block_descriptor heap_block_t;

/**
 * @brief Una estructura que representa un heap del kernel.
 */
typedef struct heap {
    heap_block_t *head;             /**< Puntero al primer bloque en el heap. */
    page_flags_t flags;             /**< Las flags de las páginas para el heap del proceso. */
} heap_t;

/**
 * @brief Inicializa el heap del kernel.
 * @param length La longitud del heap.
 *
 * @return Un puntero al primer bloque del heap.
 */
heap_t * init_kheap(pg_dir_t * dir, page_flags_t flags);

/**
 * @brief Asigna un bloque de memoria del tamaño especificado desde el heap del kernel.
 * @param size El tamaño del bloque a asignar.
 *
 * @return Una dirección virtual que apunta al comienzo del bloque asignado, o NULL si la asignación falla.
 */
virt_t kmalloc(heap_t * heap, size_t size);

/**
 * @brief Asigna un bloque de memoria del tamaño especificado desde el heap del kernel y asegura que la dirección esté alineada con una página.
 * @param size El tamaño del bloque a asignar.
 *
 * @return Una dirección virtual que apunta al comienzo del bloque asignado, o NULL si la asignación falla.
 */
virt_t kmallocp(heap_t * heap, size_t size);

/**
 * @brief Asigna un bloque de memoria del tamaño especificado desde el heap del kernel y asegura que la dirección virtual sea la indicada
 * @param size El tamaño del bloque a asignar.
 * @param address El valor de dirección virtual al que debe apuntar el bloque
 *
 * @return El bloque asignado con la dirección virtual indicada, o NULL si la asignación falla.
 */
virt_t kmalloca(heap_t * heap, size_t size, virt_t address);

#endif