# $Id$
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
#

include mk/script/script-common.mk

ifndef PERSIST_OBJECTS
$(error PERSIST_OBJECTS is not defined, nothing to serialize)
endif

# All incoming variables must be flattened on order to prevent
# expanding them once again.
override PERSIST_OBJECTS := $(PERSIST_OBJECTS)

$(info # $(GEN_BANNER))
$(info )
$(info $(\h) PERSIST_OBJECTS:)
$(foreach o,$(or $(PERSIST_OBJECTS),<nothing>),$(info $(\h)   $o))
$(info )

ifdef PERSIST_REALLOC

override PERSIST_REALLOC := $(PERSIST_REALLOC)
__persist_id_provider = \
	$(foreach id,.$(PERSIST_REALLOC)$(call alloc,$(PERSIST_REALLOC)),$(info \
		$(id).__serial_id__ := $(id))$(id))

$(info # The following objects have been sealed to prevent further serialization.)
$(info $(call object_graph_print,$(PERSIST_OBJECTS),__persist_id_provider))

else

$(info $(call object_graph_print,$(PERSIST_OBJECTS)))

endif # PERSIST_REALLOC

ifdef PERSIST_VARIABLE

override PERSIST_VARIABLE := $(PERSIST_VARIABLE)

$(info # List of objects requested to be serialized explicitly.)
$(info $(PERSIST_VARIABLE) := \
	$(foreach o,$(PERSIST_OBJECTS),\$(\n)$(\t)$($o.__serial_id__)))
$(info )

endif # PERSIST_VARIABLE
