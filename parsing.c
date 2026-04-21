#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int layer_sizes[10]; // Количество нейронов в каждом слое
    int num_layers; // Общее число слоёв
    double learning_rate; // Скорость обучения
    double regularization; // Коэффициент L2 регуляризации
} NetworkConfig;

// Функция для чтения конфигурации из файла
int load_config(const char* filename, NetworkConfig* config) {
    FILE* file = fopen(filename, "r");
    char line[256];

    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return -1;
    }
        
    while (fgets(line, sizeof(line), file)) {

        if (line[0] == '\n' || line[0] == '#') continue; // Пропускаем пустые строки и комментарии
            
        // Читаем количество нейронов по слоям
        if (strncmp(line, "neurons:", 8) == 0) {
            char* ptr = line + 8; // Пропускаем "neurons:"
            config->num_layers = 0;
                
            // Парсим числа через запятую
            while (*ptr && config->num_layers < 10) {
                while (*ptr == ' ' || *ptr == ',') ptr++; // Пропускаем пробелы и запятые
                if (*ptr == '\n' || *ptr == '\0') break;
                    
                config->layer_sizes[config->num_layers] = atoi(ptr);
                config->num_layers++;
                    
                // Двигаемся до следующего числа или конца строки
                while (*ptr >= '0' && *ptr <= '9') ptr++;
            }
        }
        // Читаем learning_rate
        else if (strncmp(line, "learning_rate:", 14) == 0) {
            config->learning_rate = atof(line + 14);
        }
        // Читаем regularization
        else if (strncmp(line, "regularization:", 15) == 0) {
            config->regularization = atof(line + 15);
        }
    }
        
    fclose(file);
    return 0;
}


int main() {
    NetworkConfig config;
    
    if (load_config("config.txt", &config) != 0) {
        return 1;
    }
    
    printf("Конфигурация загружена:\n");
    printf("Количество слоёв: %d\n", config.num_layers);
    printf("Нейроны по слоям: ");

    for (int i = 0; i < config.num_layers; i++) {
        printf("%d", config.layer_sizes[i]);
        if (i < config.num_layers - 1) printf(", ");
    }

    printf("\n");
    printf("Learning rate: %.6f\n", config.learning_rate);
    printf("Regularization (L2): %.4f\n\n", config.regularization);
    
    return 0;
}
