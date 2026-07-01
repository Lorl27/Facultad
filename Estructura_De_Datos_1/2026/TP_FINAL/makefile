# Makefile para ejecutar los casos de prueba.

#Nombre ejecutable
TARGET = testeador

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Archivos que conforman el ejecutable
OBJ = main.o sudoku.o

#Regla general - lo compila
all: $(TARGET)

# Target depende de OBJ
# Equivalente a: gcc -Wall -Wextra -g -o testeador main.o sudoku.o 
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regla para compilar .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Regla para automatizar los casos de prueba
test: $(TARGET)
	@echo "\n=== INICIANDO PRUEBAS ==="
	@for file in CasosDePrueba/*.txt; do \
		echo "\n-> Testeando archivo: $$file"; \
		./$(TARGET) $$file; \
	done
	@echo "\n=== PRUEBAS FINALIZADAS ==="

# Regla para testear TODO con Valgrind
valgrind: $(TARGET)
	@echo "\n=== INICIANDO PRUEBAS CON VALGRIND ==="
	@for file in CasosDePrueba/*.txt; do \
		echo "\n-> Analizando memoria en: $$file"; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(TARGET) $$file; \
	done
	@echo "\n=== PRUEBAS FINALIZADAS ==="

# Regla para generar n<3 tableros aleatorios con solución única.
run: $(TARGET)
	./$(TARGET)

# Limpieza
clean: 
	rm -f $(OBJ) $(TARGET)

# Limpia y recompila todo
rebuild:
	rm -f $(OBJ) $(TARGET)
	$(MAKE) all

# Declaramos que NO son archivos, sino reglas.
.PHONY: all clean rebuild test valgrind run