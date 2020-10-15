/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
*/

#ifndef ACPI_H
#define ACPI_H

#include <stddef.h>
#include <kernel/ascii.h>
#include <kernel/types.h>
#include <kernel/syscall.h>
#include <kernel/error.h>
#include <kernel/types.h>
#include "kshell.h"
#include "keyboard.h"
#include "console.h"
#include "string.h"
#include "rtc.h"
#include "kmalloc.h"
#include "page.h"
#include "process.h"
#include "main.h"
#include "fs.h"
#include "syscall_handler.h"
#include "clock.h"
#include "kernelcore.h"
#include "bcache.h"
#include "kprintf.h"
#include "ata.h"
#include "bitmap.h"
#include "x86.h"
#include "ioports.h"

struct RSDPDescriptor
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
} __attribute__((packed));

struct ACPISDTHeader
{
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} __attribute__((packed));

struct RSDT
{
    struct ACPISDTHeader h;
    uint32_t PointerToOtherSDT[16];
} __attribute__((packed));

struct GenericAddressStructure
{
    uint8_t AddressSpace;
    uint8_t BitWidth;
    uint8_t BitOffset;
    uint8_t AccessSize;
    uint32_t Address;
} __attribute__((packed));

struct FADT
{
    struct ACPISDTHeader h;
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;

    // field used in ACPI 1.0; no longer in use, for compatibility only
    uint8_t Reserved;

    uint8_t PreferredPowerManagementProfile;
    uint16_t SCI_Interrupt;
    uint32_t SMI_CommandPort;
    uint8_t AcpiEnable;
    uint8_t AcpiDisable;
    uint8_t S4BIOS_REQ;
    uint8_t PSTATE_Control;
    uint32_t PM1aEventBlock;
    uint32_t PM1bEventBlock;
    uint32_t PM1aControlBlock;
    uint32_t PM1bControlBlock;
    uint32_t PM2ControlBlock;
    uint32_t PMTimerBlock;
    uint32_t GPE0Block;
    uint32_t GPE1Block;
    uint8_t PM1EventLength;
    uint8_t PM1ControlLength;
    uint8_t PM2ControlLength;
    uint8_t PMTimerLength;
    uint8_t GPE0Length;
    uint8_t GPE1Length;
    uint8_t GPE1Base;
    uint8_t CStateControl;
    uint16_t WorstC2Latency;
    uint16_t WorstC3Latency;
    uint16_t FlushSize;
    uint16_t FlushStride;
    uint8_t DutyOffset;
    uint8_t DutyWidth;
    uint8_t DayAlarm;
    uint8_t MonthAlarm;
    uint8_t Century;

    // reserved in ACPI 1.0; used since ACPI 2.0+
    uint16_t BootArchitectureFlags;

    uint8_t Reserved2;
    uint32_t Flags;

    struct GenericAddressStructure ResetReg;

    uint8_t ResetValue;
    uint8_t Reserved3[3];
} __attribute__((packed));
struct RSDT *rsdt;
struct FADT *facp;
struct ACPISDTHeader *dsdt;

uint32_t acpi_handler(int_regs_t *regs);
void _page_map(uint32_t p_addr, uint32_t v_addr, uint32_t length);
void acpi_enable();
void acpi_power_down();
void acpi_reset();
void acpi_power_button_enable();
uint8_t acpi_checksum(void *ptr, uint32_t size, uint8_t checksum);
uint32_t acpi_handler(int_regs_t *regs);
uint32_t acpi_init();
uint8_t *acpi_search_S5(struct ACPISDTHeader *hdr);

#endif // !ACPI_H
