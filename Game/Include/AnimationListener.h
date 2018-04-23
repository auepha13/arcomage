namespace arcomage {
	class AnimationListener {
	public:
		virtual void animationStarted() = 0;
		virtual void animationFinished() = 0;
		virtual Gamestate getState() = 0;
		virtual void notifyAnimationIdle() = 0;
	};
}
