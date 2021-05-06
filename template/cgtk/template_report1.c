#include <gtk/gtk.h>

#include <libgnomeprint/gnome-print.h>
#include <libgnomeprintui/gnome-print-job-preview.h>

static void
draw_@VarFormName@(GnomePrintContext *pc, int page)
{
	gchar *txt;
	
	gnome_print_beginpage(pc, "1");
//	gnome_print_moveto(pc, 50,50);
//	gnome_print_show(pc, "print test");
	
	@VarPrintTitle@
	
	txt = g_strdup_printf("Page %i", page);
	gnome_print_moveto(pc, 50, 800);
	gnome_print_show(pc, txt);
	g_free(txt);

	gnome_print_showpage(pc);
}

GtkWidget*
create_@VarFormName@()
{
	GnomePrintContext *gpc;
	GnomePrintJob *pjob;
	GtkWidget *preview;

	pjob = gnome_print_job_new(NULL);
	gpc = gnome_print_job_get_context(pjob);
	
	draw_@VarFormName@(gpc, 1);
	draw_@VarFormName@(gpc, 2);
	gnome_print_job_close(pjob);
	preview = gnome_print_job_preview_new(pjob, "@VarForm(TITLE)@");
}
