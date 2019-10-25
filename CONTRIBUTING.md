# Contributing to NATO Lights

Welcome! NATO Lights are made better by the people who contribute to it. You can add/change lighting patterns or improve the overall system. This guide will walk you through modifying a pattern.

## Requirements

- A GitHub account
- git installed on your computer. [Learn how to install it](https://help.github.com/en/articles/set-up-git)
- (TODO): Probably a way to compile arduino code?

## Setup Local Project

1. [Create a fork](https://help.github.com/en/articles/fork-a-repo) of this project
2. Clone the project:
```bash
git clone https://github.com/<YOUR_GITHUB_USERNAME>/nato-lights.git
```
If you've set up this device with SSH, you can do this instead:
```bash
git clone git@github.com:<YOUR_GITHUB_USERNAME>/nato-lights.git
```
3. Navigate to the project
```bash
cd nato-lights
```

## Modifying a pattern

1. Choose a pattern to modify. If this pattern was written by someone else, consider duplicating their pattern and changing the name slightly, or ask them first.
2. Create a new branch
```bash
git checkout -b modify-<PATTERN NAME>
```
3. Make your changes.
4. Test your changes.
5. Commit your changes.
```bash
git add <NAME OF FILE MODIFIED>
git commit -m "feat(pattern): <CHANGE> to <PATTERN>"
```
The commit message roughly follows the [Conventional Commits Standard](https://www.conventionalcommits.org/en/v1.0.0-beta.4/).

### Push Your Changes and Creating a Pull Request

**Note:** If you're having trouble pushing your changes to GitHub, your local branch of the repository may not be up-to-date with the current repository because of additions from other contributors. Before you push your changes to GitHub, you might need to [sync your fork with the upstream repository](https://help.github.com/en/articles/syncing-a-fork).

6. Push your changes to GitHub by running:
```bash
git push origin modify-<PATTERN NAME>
```

Afterwards head to GitHub and [follow these instructions](https://help.github.com/en/articles/creating-a-pull-request-from-a-fork) to create a pull request from your fork against the `master` branch of https://github.com/DThought/nato-lights.

## Adding a new pattern

(TODO): Add description of conventions for patterns

## Other changes

IDK, talk to Will

## Attribution

Much of the language in this doc was taken from github.com/twilio-labs/open-pixel-art.
