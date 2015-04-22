import javax.swing.*;

/**
 * You need to add an event handler that will switch the JPanels in the view
 * when the user clicks the button.
 * <br>
 * Controller class created and listener registered to the view.
 * The "Switch Panels" button will now switch between the two JPanels.
 * 
 * @author Tom Bylander
 * @author Paul Szyller
 */
public class PanelSwitcher {

    public static void main(String[] args) {
        PanelSwitcherModel model = new PanelSwitcherModel();
        PanelSwitcherView view = new PanelSwitcherView();
        PanelSwitcherController controller = new PanelSwitcherController(view, model);
        
        view.registerListener(controller);

        view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        view.setSize(400,300);
        view.setVisible(true);
    }

}
