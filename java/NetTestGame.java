public class NetTestGame {

    public static void main(String[] args) {
        if (args.length != 2 && args.length != 3 && args.length != 4) {
            // Wrong number of arguments; print usage string.
            String s
                = "\nUsage: TestGame BLACK WHITE [TIMELIMIT]\n"
                + "  BLACK/WHITE - c++ program name or:\n"
                + "    SimplePlayer, ConstantTimePlayer, BetterPlayer - AIs\n"
                + "    Human - manual input\n"
                + "  TIMELIMIT - optional timelimit for each player in milliseconds:\n"
                + "  -silent - optional flag for suppressing the pretty pictures. Must come at the end.\n";
            System.out.println(s);
            System.exit(-1);
        }
        
        // Initialize the players.
        int which = 1;
        OthelloPlayer[] players = new OthelloPlayer[2];
        for (int i = 0; i < 2; i++) {
            if (args[i].equalsIgnoreCase("SimplePlayer")) {
                players[i] = new SimplePlayer();
            } else if (args[i].equalsIgnoreCase("ConstantTimePlayer")) {
                players[i] = new ConstantTimePlayer();
            } else if (args[i].equalsIgnoreCase("BetterPlayer")) {
                players[i] = new BetterPlayer();
            } else if (args[i].equalsIgnoreCase("Human")) {
                players[i] = new OthelloDisplay(which++);
            } else {
                players[i] = new WrapperPlayer("neuralnetplayer", args[i]);
            }             
        }
        
        // Start the game.
        OthelloObserver o = null;
        int silent = 1;
        if (args.length == 2 || !(args[2].equalsIgnoreCase("-silent")))
        {
            silent = 0;
        }
        if (args.length == 4) {
            silent = 1;
        }
        if (silent == 0){ o = new OthelloDisplay(); }
        OthelloGame g = null;
        if (args.length == 2 || args[2].equalsIgnoreCase("-silent")) {
            // No timeout arg given; use unlimited time.
            g = new OthelloGame(players[0], players[1], o);
        } else {
            // Parse timeout arg.       
            try {
                long timeout = Integer.parseInt(args[2]);        
                g = new OthelloGame(players[0], players[1], o, timeout);                            
            } catch (Exception e) {
                System.out.println("Error: Could not parse integer from '" + args[2] + "'");
                System.exit(-1);
            }
        }
        System.out.println("Starting game");
        if (silent == 0) {
            g.run();
        } else {
            OthelloSide w = g.runCheck();
            if (w != null) {
                System.out.println(w.toString());
            } else {
                System.out.println("Could not detemine a winner.");
            }
        }
    }
}
