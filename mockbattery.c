#include <linux/init.h>
#include <linux/module.h>
#include <linux/power_supply.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patirk Nyman");
MODULE_DESCRIPTION("A simple Linux Power Supply driver that mocks battery status");
MODULE_VERSION("0.1");

#define VERBOSE_LEVEL 4
#define DEBUG_LEVEL 3
#define INFO_LEVEL 2
#define WARNING_LEVEL 1

//Define power supply proptery struct
static enum power_supply_property sbs_properties[] = {
    /*  this attribute represents operating status */
	POWER_SUPPLY_PROP_STATUS,           
    /*  represents health of the battery,
        values corresponds to POWER_SUPPLY_HEALTH_*,
        defined in battery.h. */
	//POWER_SUPPLY_PROP_HEALTH,
    
	//POWER_SUPPLY_PROP_VOLTAGE_NOW,
	//POWER_SUPPLY_PROP_CURRENT_NOW,

    /* relative state of charge in % */
	POWER_SUPPLY_PROP_CAPACITY

    /* seconds left for battery to be considered empty (i.e.
    while battery powers a load) */
	//POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
    /* seconds left for battery to be considered full (i.e.
    while battery is charging) */
	//POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
};

static int get_battery_property(struct power_supply *psy,
					   enum power_supply_property psp,
					   union power_supply_propval *val)
{
    switch(psp) {
    case POWER_SUPPLY_PROP_STATUS:
        val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
        break;
    case POWER_SUPPLY_PROP_CAPACITY:
        val->intval = 87;
        break;
    default: 
        pr_err("%s: some properties deliberately report errors.\n",
        __func__);
        return -EINVAL;
    }

    return 0;
}

static const struct power_supply_desc psy_desc = {
    .name = "mock_battery",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = sbs_properties,
	.num_properties = ARRAY_SIZE(sbs_properties),
	.get_property = get_battery_property,
};

static struct power_supply *psy;

static int __init m_init(void) {
    //Register the power supply module
    int ret;

    psy = power_supply_register(NULL,
            &psy_desc, NULL);

    if(IS_ERR(psy)) {
        pr_err("Failed to register power supply\n");
        goto failed_psy_reg;
    }
    ret = 0;
    pr_info("Successfully registered power supply device");

    return ret;
failed_psy_reg:
    power_supply_unregister(psy);
    return -1;
}

static void __exit m_exit(void) {
    power_supply_unregister(psy);
    pr_info("I am leaving this world\n");
}

module_init(m_init);
module_exit(m_exit);