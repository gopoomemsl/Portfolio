import java.awt.event.*;

/**
 * This Controller class only handles the one button to switch 
 * between the two JPanels, it is therefore very short.
 * 
 * @author Paul Szyller
 */
public class PanelSwitcherController implements ActionListener
{
	private PanelSwitcherModel model;
	
	private PanelSwitcherView view;
	
	/**
	 * We pass in the view and model for this MVC application.
	 * @param view
	 * @param model
	 */
	public PanelSwitcherController (PanelSwitcherView view, PanelSwitcherModel model)
	{
		this.model = model;
		this.view = view;
	}
	
	/**
	 * Switches the panels in the model, then display the current panel in the view.
	 */
	public void actionPerformed (ActionEvent event)
	{
		model.switchPanel();
		view.displayPanel(model.whichPanel());
	}
}
