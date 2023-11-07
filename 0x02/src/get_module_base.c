#include <get_module_base.h>
#include <get_pid.h>

t_base_address ac_base_address;

unsigned long get_module_base(const char *module) {
    memset(ac_base_address.file_maps, INITIALIZE_MEMORY, BUFFER_SIZE);
    memset(ac_base_address.line, INITIALIZE_MEMORY, BUFFER_SIZE);
    memset(ac_base_address.get_first_line, INITIALIZE_MEMORY, FIRST_LINE_SIZE);

    sprintf(ac_base_address.file_maps, "/proc/%d/maps", process_pid.pid);
    sprintf(ac_base_address.real_module, "/%s", module);

    ac_base_address.get_module_base_address_file = fopen(ac_base_address.file_maps, "r");

    if (ac_base_address.get_module_base_address_file != NULL) {
        while(fgets(ac_base_address.line, BUFFER_SIZE, ac_base_address.get_module_base_address_file)) {
            if(strstr(ac_base_address.line, ac_base_address.real_module)) {
                strncpy(ac_base_address.get_first_line, ac_base_address.line, ADDRESS_OFFSET);
                ac_base_address.convert_module = strtoul(ac_base_address.get_first_line, NULL, 16);
                break;
            }
        }
    }
    fclose(ac_base_address.get_module_base_address_file);
    return ac_base_address.convert_module;
}
