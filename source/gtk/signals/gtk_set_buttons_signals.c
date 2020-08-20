#include "gtk_module.h"

void	gtk_set_buttons_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_shape),
		"clicked", G_CALLBACK(new_shape), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_light),
		"clicked", G_CALLBACK(new_light), rt);
}
