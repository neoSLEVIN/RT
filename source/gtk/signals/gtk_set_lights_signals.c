#include "gtk_module.h"

void	gtk_set_lights_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.lights.select),
		"changed", G_CALLBACK(lights_tree_selection_changer), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.lights.tree),
		"button-press-event", G_CALLBACK(lights_tree_single_click), rt);
}
