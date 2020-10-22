#include "ide.h"

#define SECTOR_COUNT 2
#define LBA_LOW 3
#define LBA_MID 4
#define LBA_HIG 5

uint8_t ide_bus, ide_dev, ide_fun;

uint16_t ide_primary_io_base, ide_primary_ctrl, ide_secondary_io_base, ide_secondary_ctrl, ide_bus_master_base;

void ide_init(void)
{

    if (!PCI_GetClassCodes(&ide_bus, &ide_dev, &ide_fun)) // find mass storage / scsi bus
        return;

    if ((ide_primary_io_base = PCI_ConfigReadWord(ide_bus, ide_dev, ide_fun, PCI_BAR0)) <= 1)
        ide_primary_io_base = 0x1F0;

    if ((ide_primary_ctrl = PCI_ConfigReadWord(ide_bus, ide_dev, ide_fun, PCI_BAR1)) <= 1)
        ide_primary_ctrl = 0x3F6;

    if ((ide_secondary_io_base =
             PCI_ConfigReadWord(ide_bus, ide_dev, ide_fun, PCI_BAR2)) <= 1)
        ide_secondary_io_base = 0x170;

    if ((ide_secondary_ctrl =
             PCI_ConfigReadWord(ide_bus, ide_dev, ide_fun, PCI_BAR3)) <= 1)
        ide_secondary_ctrl = 0x376;

    ide_bus_master_base =
        PCI_ConfigReadWord(ide_bus, ide_dev, ide_fun, PCI_BAR4);

    uint8_t i;
    kprintf("[ide] PRI: ");
    for (i = 2; i < 6; i++)
        kprintf("0x%x ", inb(ide_primary_io_base + i));
    kprintf(", ");
    kprintf("SEC: ");
    for (i = 2; i < 6; i++)
        kprintf("0x%x ", inb(ide_secondary_io_base + i));
    kprintf("\n");
}
